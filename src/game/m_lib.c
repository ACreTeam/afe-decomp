/**
 * @file m_lib.c
 * @brief Utility functions for various mathematical and memory operations.
 *
 * This file contains a collection of utility functions used for various mathematical
 * and memory operations. These functions include:
 *
 * - mem_copy(): Copy memory from one location to another.
 * - mem_clear(): Clear (set) a memory area to a given value.
 * - mem_cmp(): Compare two memory areas.
 * - cos_s(): Calculate the cosine of a short angle.
 * - sin_s(): Calculate the sine of a short angle.
 * - chase_angle(): Chase an angle with a given step value.
 * - chase_s(): Chase a short integer value with a given step value.
 * - chase_f(): Chase a float value with a given step value.
 * - chase_xyz_t(): Chase an xyz_t structure value with a given fraction value.
 * - chase_angle2(): Chase an angle with a given step value and limit.
 * - inter_float(): Interpolate between two float values with a given step value.
 * - get_random_timer(): Get a random timer value with a base and range.
 * - xyz_t_move(): Move an xyz_t value from a source to a destination.
 * - xyz_t_move_s_xyz(): Move an xyz_t value from an s_xyz source to a destination.
 * - xyz_t_add(): Add two xyz_t values.
 * - xyz_t_sub(): Subtract two xyz_t values.
 * - xyz_t_mult_v(): Multiply an xyz_t value by a scalar.
 * - search_position_distance(): Calculate the distance between two 3D positions.
 * - search_position_distanceXZ(): Calculate the horizontal distance between two 3D positions.
 * - search_position_angleY(): Calculate the Y angle between two 3D positions.
 * - search_position_angleX(): Calculate the X angle between two 3D positions.
 * - add_calc(): Update a float value towards a target with a given fraction, max step, and min step.
 * - add_calc2(): Update a float value towards a target with a given fraction and max step.
 * - add_calc0(): Update a float value with a given fraction and max step.
 * - add_calc_short_angle2(): Update a short angle value towards a target with given fraction, max step, and min step.
 * - add_calc_short_angle3(): Update a short angle value towards a target with given fraction, max step, and min step.
 * - rgba_t_move(): Move an rgba_t value from a source to a destination.
 * - none_proc1(): A general no-op function that returns 0.
 * - none_proc2(): A no-op function meant for ACTORs which does nothing.
 * - _Game_play_isPause(): Check if the game is paused.
 * - check_percent_abs(): Calculate a percentage value with scaling and optional shifting.
 * - get_percent_forAccelBrake(): Calculate a percentage value for acceleration and braking.
 * - Game_play_Projection_Trans(): Transform a world position into screen space.
 * - get_percent(): Calculate a percentage value given a min and max range.
 */

#include "m_lib.h"

#include "game.h"
#include "m_actor.h"
#include "m_play.h"
#include "main.h"
#include "libultra/libultra.h"
#include "MSL_C/w_math.h"
#include "libc64/qrand.h"
#include "sys_matrix.h"
#include "sys_math.h"
#include "sys_math3d.h"

static u32 countsum9[512+1];
static u32 count9[512];
static u32 countsum11[4096+1];
static u32 count11[4096];
static u16 skip[256];

static void initskip(u8* pattern, s32 pattern_len);
static int mischarsearch(u8* pattern, int pattern_len, u8* text, int text_len);
static void search2(u8 *data, int start_idx, int data_size, int *out_offset, int *out_length, int window_size);
static int encode_asrsub(u8* compress_buf, u8* src, int size, int count11_size);

extern int encode_asr(u8* compress_buf, u8* src, int size) {
    int result = encode_asrsub(compress_buf, src, size, (1 << (11 + 1)));

    compress_buf[0] = 'A';
    compress_buf[1] = 'S';
    compress_buf[2] = 'R';
    compress_buf[3] = '0';
    compress_buf[4] = 0x80 | ((size >> 24) & 0xFF);
    compress_buf[5] = (size >> 16) & 0xFF;
    compress_buf[6] = (size >> 8) & 0xFF;
    compress_buf[7] = size & 0xFF;

    return result;
}

int encode_asrsub(u8 *encodeBuffer, u8 *data, int size, int count11Size) {
    int sym_count;
    int search_window_size;
    int rescale_count;
    int i;
    int flush_count;
    int encodeSize;
    int sym;
    int sym2;
    u32 step;
    u32 range;
    u32 low;
    u32 temp;
    int match_dist1;
    int match_len1;
    int match_dist2;
    int match_len2;
    int readIdx;
    int total_syms;
    int total_matches;
    u8 *lit_buf;
    u8 *dist_buf;
    int count11_limit;

    count11_limit = count11Size;
    search_window_size = count11_limit;
    total_syms = total_matches = readIdx = 0;
    sym = (size + 7) / 8 + 8;
    temp = sym;
    temp += size;
    temp = size + temp;
    lit_buf = encodeBuffer + (size << 1);
    dist_buf = encodeBuffer + temp * 2;

    while (readIdx < size) {
        search2(data, readIdx, size, &match_dist1, &match_len1, search_window_size);

        if (match_len1 >= 3) {
            search2(data, readIdx + 1, size, &match_dist2, &match_len2, search_window_size);

            if (match_len1 + 1 < match_len2) {
                *(u16 *)(lit_buf + total_syms++ * 2) = data[readIdx];
                readIdx++;
                match_len1 = match_len2;
                match_dist1 = match_dist2;
            }

            match_dist1 = (readIdx - match_dist1) - 1;
            *(u16 *)(lit_buf + total_syms++ * 2) = (match_len1 - 3) | 0x100;
            readIdx += match_len1;
            *(u16 *)(dist_buf + total_matches++ * 2) = match_dist1;
        } else {
            *(u16 *)(lit_buf + total_syms++ * 2) = data[readIdx];
            readIdx++;
        }
    }

    countsum9[0] = 0;
    range = 0xFFFFFFFF;
    low = 0;
    for (i = 0; i < 0x200; i++) {
        count9[i] = 1;
        countsum9[i + 1] = countsum9[i] + 1;
    }

    sym_count = 0;
    encodeSize = 0xC;
    while (sym_count < total_syms) {
        sym = *(u16 *)(lit_buf + sym_count++ * 2);

        step = range / countsum9[0x200];
        low += step * countsum9[sym];
        range = step * count9[sym];
        count9[sym]++;

        while (++sym <= 0x200) {
            countsum9[sym]++;
        }

        if (countsum9[0x200] >= 0x10000) {
            countsum9[0] = 0;
            for (i = 0; i < 0x200; i++) {
                count9[i] = (count9[i] >> 1) | 1;
                countsum9[i + 1] = countsum9[i] + count9[i];
            }
        }

        while ((low & 0xFF000000) == ((low + range) & 0xFF000000)) {
            encodeBuffer[encodeSize] = (u8)(low >> 24);
            low <<= 8;
            range <<= 8;
            encodeSize++;
        }
        while (range < 0x10000) {
            temp = low & 0xFFFF;
            range = (0x10000 - temp) << 8;
            encodeBuffer[encodeSize] = (u8)(low >> 24);
            low <<= 8;
            encodeSize++;
        }
    }

    for (flush_count = 4; flush_count > 0; flush_count--) {
        encodeBuffer[encodeSize] = (u8)(low >> 24);
        low <<= 8;
        encodeSize++;
    }

    encodeBuffer[8]  = (u8)((u32)encodeSize >> 24);
    encodeBuffer[9]  = (u8)((u32)encodeSize >> 16);
    encodeBuffer[10] = (u8)((u32)encodeSize >> 8);
    encodeBuffer[11] = (u8)encodeSize;

    low = 0;
    range = 0xFFFFFFFF;
    countsum11[0] = 0;
    for (i = 0; i < count11_limit; i++) {
        count11[i] = 1;
        countsum11[i + 1] = countsum11[i] + 1;
    }

    sym_count = 0;
    while (sym_count < total_matches) {
        sym2 = *(u16 *)(dist_buf + sym_count++ * 2);

        step = range / countsum11[count11_limit];
        low += step * countsum11[sym2];
        range = step * count11[sym2];
        count11[sym2]++;

        while (++sym2 <= count11_limit) {
            countsum11[sym2]++;
        }

        if (countsum11[count11_limit] >= 0x10000) {
            countsum11[0] = 0;
            for (i = 0; i < count11_limit; i++) {
                count11[i] = (count11[i] >> 1) | 1;
                countsum11[i + 1] = countsum11[i] + count11[i];
            }
        }

        while ((low & 0xFF000000) == ((low + range) & 0xFF000000)) {
            encodeBuffer[encodeSize] = (u8)(low >> 24);
            low <<= 8;
            range <<= 8;
            encodeSize++;
        }
        while (range < 0x10000) {
            temp = low & 0xFFFF;
            range = (0x10000 - temp) << 8;
            encodeBuffer[encodeSize] = (u8)(low >> 24);
            low <<= 8;
            encodeSize++;
        }
    }

    for (flush_count = 4; flush_count > 0; flush_count--) {
        encodeBuffer[encodeSize] = (u8)(low >> 24);
        low <<= 8;
        encodeSize++;
    }

    return encodeSize;
}

static void search2(u8 *data, int start_idx, int data_size, int *out_offset, int *out_length, int window_size) {
    int skip;
    u8 *target_base;
    int max_len;
    u8 *cur;
    int search_pos;
    int best_offset;
    int best_len;

    best_len = 3;
    search_pos = (start_idx > window_size) ? (start_idx - window_size) : 0;
    if (data_size - start_idx > 0x102) {
        max_len = 0x102;
    } else {
        max_len = data_size - start_idx;
    }
    if ((int)max_len < 3) {
        *out_length = 0;
        *out_offset = 0;
    } else {
        target_base = data + start_idx;
        goto search_next;

        while (1) {
            while (best_len < max_len) {
                if (cur[skip + best_len] != target_base[best_len]) {
                    break;
                }
                best_len = best_len + 1;
            }
            if (best_len == max_len) {
                *out_offset = search_pos + skip;
                *out_length = max_len;
                return;
            }
            best_offset = search_pos + skip;
            search_pos = skip + search_pos;
            search_pos = search_pos + 1;
            best_len = best_len + 1;

search_next:
            if ((int)search_pos >= start_idx) {
                break;
            }
            cur = data + search_pos;
            skip = mischarsearch(target_base, best_len, cur, (start_idx + best_len) - search_pos);
            if (skip < start_idx - search_pos) {
                continue;
            }
            break;
        }
        *out_offset = best_offset;
        *out_length = (best_len > 3) ? (best_len - 1) : 0;
    }
}

int mischarsearch(u8* pattern, int pattern_len, u8* text, int text_len) {
    int shift_amount;
    u8* pattern_ptr;
    u8* text_ptr;
    int text_idx;
    int pattern_cmp;
    u8 last_char;

    if (pattern_len > text_len) {
        return text_len;
    }

    initskip(pattern, pattern_len);

    pattern_ptr = pattern;
    pattern_ptr += pattern_len;
    text_idx = pattern_len - 1;
    last_char = pattern_ptr[-1];

    while (1) {
        do {
            if (last_char == text[text_idx]) {
                break;
            }

            text_idx = text_idx + skip[text[text_idx]];
        } while (1);

        text_idx = text_idx - 1;
        pattern_cmp = pattern_len - 2;

        goto compare_pattern;

mismatch:
        shift_amount = skip[*text_ptr];
        if (pattern_len - pattern_cmp > shift_amount) {
            shift_amount = pattern_len - pattern_cmp;
        }
        text_idx = text_idx + shift_amount;
        continue;

compare_pattern:
        while (pattern_cmp >= 0) {
            text_ptr = text + text_idx;
            if (*text_ptr != pattern[pattern_cmp]) {
                goto mismatch;
            }

            text_idx = text_idx - 1;
            pattern_cmp = pattern_cmp - 1;
        }

        break;
    }

    return text_idx + 1;
}

static void initskip(u8* pattern, s32 pattern_len) {
    int i;

    // Step 1: Initialize the entire table to the maximum jump distance
    // 0x100 is 256, representing all possible values of a 1-byte character.
    for (i = 0; i < 256; i++) {
        skip[i] = pattern_len;
    }

    // Step 2: Populate the skip distances for characters actually in the pattern
    for (i = 0; i < pattern_len; i++) {
        u8 current_char = pattern[i];
        
        // Calculate distance from the current character to the end of the pattern
        skip[current_char] = pattern_len - i - 1;
    }
}

int decode_asr(u8 *in, u8 *out) {
    int symbol;
    u32 step;
    int model_index;
    int dist_in_pos;
    int low_bound;
    int copy_src;
    int literal_in_pos;
    int out_pos;
    int target_size;
    u32 literal_range;
    u32 range_adjust;
    int high_bound;
    u32 dist_range;
    u32 literal_low;
    u32 dist_low;
    u32 literal_code;
    int i;
    u32 dist_code;
    int j;
    int dist_model_size;
    u32 scaled_value;

    target_size = (in[5] << 16) | (in[6] << 8) | in[7];
    dist_in_pos = (in[8] << 24) | (in[9] << 16) | (in[10] << 8) | in[11];
    dist_model_size = (in[4] & 0x80) ? 0x1000 : 0x200;
    dist_range = 0xFFFFFFFF;
    literal_range = 0xFFFFFFFF;
    literal_low = dist_low = 0;
    countsum9[0] = countsum11[0] = 0;

    // Literal/length model: 0x00-0xFF are literals, 0x100+ are match lengths.
    for (i = 0; i < 0x200; i++) {
        count9[i] = 1;
        countsum9[i + 1] = countsum9[i] + 1;
    }

    // Distance model size depends on the high bit in the header flags.
    for (i = 0; i < dist_model_size; i++) {
        count11[i] = 1;
        countsum11[i + 1] = countsum11[i] + 1;
    }

    out_pos = 0;
    literal_in_pos = 0x10;
    literal_code = (in[12] << 24) | (in[13] << 16) | (in[14] << 8) | in[15];
    dist_code = (in[dist_in_pos] << 24) | (in[dist_in_pos + 1] << 16) | (in[dist_in_pos + 2] << 8) | in[dist_in_pos + 3];
    dist_in_pos += 4;

    while (out_pos < target_size) {
        // Decode the next literal or match-length symbol.
        step = literal_range / countsum9[0x200];
        scaled_value = (literal_code - literal_low) / step;
        low_bound = 0;
        high_bound = 0x200;

        while (low_bound < high_bound) {
            model_index = (low_bound + high_bound) >> 1;
            if (scaled_value < countsum9[model_index]) {
                high_bound = model_index;
            } else {
                low_bound = model_index + 1;
            }
        }

        while (model_index >= 0) {
            if ((countsum9[model_index] <= scaled_value) && (scaled_value < countsum9[model_index + 1])) break;
            model_index--;
        }
        symbol = model_index;

        literal_low += step * countsum9[symbol];
        literal_range = step * count9[symbol];
        count9[symbol]++;

        while (++model_index <= 0x200) {
            countsum9[model_index]++;
        }

        if (countsum9[0x200] >= 0x10000) {
            countsum9[0] = 0;
            for (j = 0; j < 0x200; j++) {
                count9[j] = (count9[j] >> 1) | 1;
                countsum9[j + 1] = countsum9[j] + count9[j];
            }
        }

        while ((literal_low & 0xFF000000) == ((literal_low + literal_range) & 0xFF000000)) {
            literal_low <<= 8;
            literal_range <<= 8;
            literal_code = in[literal_in_pos++] + (literal_code << 8);
        }
        while (literal_range < 0x10000) {
            range_adjust = 0x10000 - (literal_low & 0xFFFF);
            literal_range = range_adjust << 8;
            literal_low <<= 8;
            literal_code = in[literal_in_pos++] + (literal_code << 8);
        }

        if (symbol < 0x100) {
            out[out_pos++] = (u8)symbol;
            continue;
        }

        // Length symbols are followed by a distance symbol for the LZ copy.
        step = dist_range / countsum11[dist_model_size];
        scaled_value = (dist_code - dist_low) / step;
        low_bound = 0;
        high_bound = dist_model_size;

        while (low_bound < high_bound) {
            model_index = (low_bound + high_bound) >> 1;
            if (scaled_value < countsum11[model_index]) {
                high_bound = model_index;
            } else {
                low_bound = model_index + 1;
            }
        }

        while (model_index >= 0) {
            if ((countsum11[model_index] <= scaled_value) && (scaled_value < countsum11[model_index + 1])) break;
            model_index--;
        }

        copy_src = out_pos - model_index - 1;
        symbol -= 0xFD;
        while (symbol > 0) {
            out[out_pos] = out[copy_src++];
            symbol--;
            out_pos++;
        }

        dist_low += step * countsum11[model_index];
        dist_range = step * count11[model_index];
        count11[model_index]++;

        while (++model_index <= dist_model_size) {
            countsum11[model_index]++;
        }

        if (countsum11[dist_model_size] >= 0x10000) {
            countsum11[0] = 0;
            for (j = 0; j < dist_model_size; j++) {
                count11[j] = (count11[j] >> 1) | 1;
                countsum11[j + 1] = countsum11[j] + count11[j];
            }
        }

        while ((dist_low & 0xFF000000) == ((dist_low + dist_range) & 0xFF000000)) {
            dist_low <<= 8;
            dist_range <<= 8;
            dist_code = in[dist_in_pos++] + (dist_code << 8);
        }
        while (dist_range < 0x10000) {
            range_adjust = 0x10000 - (dist_low & 0xFFFF);
            dist_range = range_adjust << 8;
            dist_low <<= 8;
            dist_code = in[dist_in_pos++] + (dist_code << 8);
        }

    }

    return out_pos;
}

extern void decode_szs(u8* compress_buf, u8* dst_buf) {
    int link_info;
    int offset_diff;
    int copy_len;
    int offset;
    int now_size;
    int final_size;
    u8 chk_bit;

    offset = 0x10;
    chk_bit = 0;
    now_size = 0;
    final_size = (compress_buf[4] << 24) | (compress_buf[5] << 16) | (compress_buf[6] << 8) | (compress_buf[7]);

    while (now_size < final_size) {
        u8 bits;

        if (chk_bit == 0) {
            bits = compress_buf[offset];
            offset++;
            chk_bit = 0x80;
        }

        if ((bits & chk_bit) != 0) {
            dst_buf[now_size++] = compress_buf[offset];
            offset++;
        } else {
            int i;

            link_info = (compress_buf[offset] << 8) | compress_buf[offset + 1];
            offset += 2;
            copy_len = link_info >> 12;
            offset_diff = now_size - (link_info & 0xFFF);
            if (copy_len == 0) {
                copy_len = compress_buf[offset] + 0x12;
                offset++;
            } else {
                copy_len += 2;
            }
            
            for (i = 0; i < copy_len; i++) {
                dst_buf[now_size] = dst_buf[offset_diff - 1];
                now_size++;
                offset_diff++;
            }
        }

        chk_bit >>= 1;
    }
}

/**
 * @brief Copy memory from the source buffer to the destination buffer.
 *
 * @param dst Pointer to the destination buffer.
 * @param src Pointer to the source buffer.
 * @param size Number of bytes to copy.
 */
extern void mem_copy(u8* dst, u8* src, size_t size) {
    for (; size != 0; size--) {
        *dst = *src;
        src++;
        dst++;
    }
}

/**
 * @brief Clear memory in the destination buffer by setting it to the specified value.
 *
 * @param dst Pointer to the destination buffer.
 * @param size Number of bytes to clear.
 * @param val Value to set each byte in the destination buffer.
 */
extern void mem_clear(u8* dst, size_t size, u8 val) {
    u32 i;

    for (i = 0; i < size; i++) {
        *dst++ = val;
    }
}

/**
 * @brief Compare two memory buffers for equality.
 *
 * @param p1 Pointer to the first memory buffer.
 * @param p2 Pointer to the second memory buffer.
 * @param size Number of bytes to compare.
 * @return TRUE if the memory buffers are equal, FALSE otherwise.
 */
extern int mem_cmp(u8* p1, u8* p2, size_t size) {
    for (; size != 0; size--) {
        if (*p1 != *p2) {
            return FALSE;
        }
        p1++;
        p2++;
    }
    return TRUE;
}

/**
 * @brief Calculate the cosine of the given s16 angle.
 *
 * @param angle Angle in s16 format.
 * @return Cosine of the angle as a floating-point value.
 */
extern f32 cos_s(s16 angle) {
    return coss(angle) * SHT_MINV;
}

/**
 * @brief Calculate the sine of the given s16 angle.
 *
 * @param angle Angle in s16 format.
 * @return Sine of the angle as a floating-point value.
 */
extern f32 sin_s(s16 angle) {
    return sins(angle) * SHT_MINV;
}

/**
 * @brief Chase an angle value towards a target angle, with a specified step.
 *
 * This function updates the angle value, moving it towards the target angle
 * by a specified step. The angle will not overshoot the target. The function
 * returns TRUE if the angle reaches the target, and FALSE otherwise.
 *
 * @param pValue Pointer to the angle value to be updated.
 * @param target Target angle to chase.
 * @param step Step value to be added or subtracted from the current angle.
 * @return TRUE if the angle reaches the target, FALSE otherwise.
 */
extern int chase_angle(s16* const pValue, const s16 target, s16 step) {
    if (step) {
        f32 updateScale = game_GameFrame_2F;

        if ((s16)(*pValue - target) > 0) {
            step = -step;
        }

        *pValue += (s16)(step * updateScale);

        if (((s16)(*pValue - target) * step) >= 0) {
            *pValue = target;
            return TRUE;
        }
    } else if (*pValue == target) {
        return TRUE;
    }

    return FALSE;
}

/**
 * @brief Chase a signed 16-bit value towards a target value, with a specified step.
 *
 * This function updates the value, moving it towards the target value
 * by a specified step. The value will not overshoot the target. The function
 * returns TRUE if the value reaches the target, and FALSE otherwise.
 *
 * @param pValue Pointer to the value to be updated.
 * @param target Target value to chase.
 * @param step Step value to be added or subtracted from the current value.
 * @return TRUE if the value reaches the target, FALSE otherwise.
 */
extern int chase_s(s16* const pValue, const s16 target, s16 step) {
    if (step) {
        if (*pValue > target) {
            step = -step;
        }

        *pValue += step;

        if ((step * (*pValue - target)) >= 0) {
            *pValue = target;
            return TRUE;
        }
    } else {
        if (*pValue == target) {
            return TRUE;
        }
    }
    return FALSE;
}

/**
 * @brief Chase a floating-point value towards a target value, with a specified step.
 *
 * This function updates the value, moving it towards the target value
 * by a specified step. The value will not overshoot the target. The function
 * returns TRUE if the value reaches the target, and FALSE otherwise.
 *
 * @param pValue Pointer to the value to be updated.
 * @param target Target value to chase.
 * @param step Step value to be added or subtracted from the current value.
 * @return TRUE if the value reaches the target, FALSE otherwise.
 */
extern int chase_f(f32* const pValue, const f32 target, f32 step) {
    if (step) {
        if (*pValue > target) {
            step = -step;
        }

        *pValue += step;

        if ((step * (*pValue - target)) >= 0.0f) {
            *pValue = target;
            return TRUE;
        }
    } else {
        if (*pValue == target) {
            return TRUE;
        }
    }
    return FALSE;
}

/**
 * @brief Chase an xyz_t value towards a target xyz_t value, with a specified fraction.
 *
 * This function updates the xyz_t value, moving it towards the target xyz_t value
 * by a specified fraction of the distance between the current value and the target.
 * The function returns the remaining distance after the chase.
 *
 * @param pValue Pointer to the xyz_t value to be updated.
 * @param target Pointer to the target xyz_t value to chase.
 * @param fraction Fraction of the distance to move towards the target.
 * @return Remaining distance after the chase.
 */
extern f32 chase_xyz_t(xyz_t* const pValue, const xyz_t* const target, const f32 fraction) {
    xyz_t diff;
    f32 dist;
    f32 stepSize;

    xyz_t_sub(target, pValue, &diff);

    dist = Math3DVecLength(&diff);
    if (dist > fraction) {
        stepSize = fraction / dist;
        pValue->x += stepSize * diff.x;
        pValue->y += stepSize * diff.y;
        pValue->z += stepSize * diff.z;

        return dist - fraction;
    } else {
        xyz_t_move(pValue, target);

        return 0.0f;
    }
}

/**
 * @brief Chase an angle value towards a limit angle with a specified step, considering wrap-around.
 *
 * This function updates the angle value, moving it towards the limit angle by a specified step,
 * taking into account the angle wrap-around (0 to 65535). The function returns TRUE if the value
 * reaches the limit, and FALSE otherwise.
 *
 * @param pValue Pointer to the angle value to be updated.
 * @param limit Limit angle to chase.
 * @param step Step value to be added to the current angle.
 * @return TRUE if the angle reaches the limit, FALSE otherwise.
 */
extern int chase_angle2(s16* const pValue, const s16 limit, const s16 step) {
    s16 prev = *pValue;

    *pValue += step;
    if (((s16)(*pValue - limit) * (s16)(prev - limit)) <= 0) {
        s32 absDiff = ABS((s16)(*pValue - limit));

        if (absDiff < 16384) {
            *pValue = limit;
            return TRUE;
        }
    }

    return FALSE;
}

/**
 * @brief Interpolate between a float and a target using a step.
 *
 * @param pValue Pointer to the float to be updated.
 * @param arg1 Target value for interpolation.
 * @param step Step value for interpolation speed.
 */
extern void inter_float(f32* const pValue, const f32 arg1, const int step) {
    if (step <= 0) {
        *pValue = arg1;
    } else {
        f32 diff = arg1 - *pValue;

        *pValue += diff / step;
    }
}

/**
 * @brief Generate a random timer value based on a base value and a range.
 *
 * This function generates a random timer value by adding a fraction of the specified range
 * to the base value. The random fraction is generated using fqrand().
 * Range will be [base, base + range).
 *
 * @param base Base value for the timer.
 * @param range Range value used to generate the random fraction.
 * @return Random timer value.
 */
extern s16 get_random_timer(const s16 base, const s16 range) {
    return base + (s16)(range * fqrand());
}

/**
 * @brief Copy an xyz_t to another xyz_t.
 *
 * @param dest Destination xyz_t structure.
 * @param src Source xyz_t structure.
 */
extern void xyz_t_move(xyz_t* const dest, const xyz_t* const src) {
    dest->x = src->x;
    dest->y = src->y;
    dest->z = src->z;
}

/**
 * @brief Move the content of an s_xyz structure to an xyz_t structure.
 *
 * @param dest Pointer to the destination xyz_t structure.
 * @param src Pointer to the source s_xyz structure.
 */
extern void xyz_t_move_s_xyz(xyz_t* const dest, const s_xyz* const src) {
    dest->x = src->x;
    dest->y = src->y;
    dest->z = src->z;
}

/**
 * @brief Add two xyz_t structures element-wise.
 *
 * @param augend First input xyz_t structure.
 * @param addend Second input xyz_t structure.
 * @param total Output xyz_t structure for the result.
 */

extern void xyz_t_add(const xyz_t* const augend, const xyz_t* const addend, xyz_t* const total) {
    total->x = augend->x + addend->x;
    total->y = augend->y + addend->y;
    total->z = augend->z + addend->z;
}

/**
 * @brief Subtract two xyz_t structures element-wise.
 *
 * @param minuend First input xyz_t structure.
 * @param subtrahend Second input xyz_t structure.
 * @param diff Output xyz_t structure for the result.
 */
extern void xyz_t_sub(const xyz_t* const minuend, const xyz_t* const subtrahend, xyz_t* const diff) {
    diff->x = minuend->x - subtrahend->x;
    diff->y = minuend->y - subtrahend->y;
    diff->z = minuend->z - subtrahend->z;
}

/**
 * @brief Multiply an xyz_t by a scalar.
 *
 * @param multiplicand Input xyz_t structure.
 * @param multiplier Scalar value.
 */
extern void xyz_t_mult_v(xyz_t* const multiplicand, const f32 multiplier) {
    multiplicand->x *= multiplier;
    multiplicand->y *= multiplier;
    multiplicand->z *= multiplier;
}

/**
 * @brief Calculate the Euclidean distance between two xyz_t structures.
 *
 * @param pos Pointer to the first xyz_t structure representing the position.
 * @param target Pointer to the second xyz_t structure representing the target position.
 * @return The Euclidean distance between the two xyz_t structures.
 */
extern f32 search_position_distance(const xyz_t* const pos, const xyz_t* const target) {
    f32 diffX = target->x - pos->x;
    f32 diffY = target->y - pos->y;
    f32 diffZ = target->z - pos->z;

    return sqrtf((diffX * diffX) + (diffY * diffY) + (diffZ * diffZ));
}

/**
 * @brief Calculate the Euclidean distance between two xyz_t structures in the XZ plane.
 *
 * @param pos Pointer to the first xyz_t structure representing the position.
 * @param target Pointer to the second xyz_t structure representing the target position.
 * @return The Euclidean distance between the two xyz_t structures in the XZ plane.
 */
extern f32 search_position_distanceXZ(const xyz_t* const pos, const xyz_t* const target) {
    f32 diffX = target->x - pos->x;
    f32 diffZ = target->z - pos->z;

    return sqrtf((diffX * diffX) + (diffZ * diffZ));
}

/**
 * @brief Calculate the angle in the Y axis (yaw) between two xyz_t positions.
 *
 * @param pos Pointer to the first xyz_t structure representing the current position.
 * @param target Pointer to the second xyz_t structure representing the target position.
 * @return The angle in the Y axis (yaw) between the two xyz_t positions.
 */
extern s16 search_position_angleY(const xyz_t* const pos, const xyz_t* const target) {
    f32 diffX = target->x - pos->x;
    f32 diffZ = target->z - pos->z;

    return atans_table(diffZ, diffX);
}

/**
 * @brief Calculate the angle in the X axis (pitch) between two xyz_t positions.
 *
 * @param pos Pointer to the first xyz_t structure representing the current position.
 * @param target Pointer to the second xyz_t structure representing the target position.
 * @return The angle in the X axis (pitch) between the two xyz_t structures.
 */
extern s16 search_position_angleX(const xyz_t* const pos, const xyz_t* const target) {
    f32 diffXZ = search_position_distanceXZ(pos, target);
    f32 diffY = pos->y - target->y;

    return atans_table(diffXZ, diffY);
}

/**
 * @brief Add a calculated value to a variable to approach a target value with minimum and maximum step limits.
 *
 * This function adds a calculated step size to the input variable to approach the target value.
 * The step size is calculated based on the fraction and is limited by the minimum and maximum step values.
 *
 * @param pValue Pointer to the input variable.
 * @param target Target value to approach.
 * @param fraction Fraction to use in the step size calculation.
 * @param maxStep Maximum allowed step size.
 * @param minStep Minimum allowed step size.
 * @return The difference between the updated input variable value and the target value.
 */
extern f32 add_calc(f32* pValue, f32 target, f32 fraction, f32 maxStep, f32 minStep) {
    f32 negMinStep;
    f32 stepSize;

    if (*pValue != target) {
        stepSize = fraction * (target - *pValue);
        negMinStep = -minStep;

        if ((stepSize <= negMinStep) || (minStep <= stepSize)) {
            if (stepSize > maxStep) {
                stepSize = maxStep;
            } else if (stepSize < -maxStep) {
                stepSize = -maxStep;
            }

            *pValue += stepSize;

            if (stepSize > 0.0f) {
                if (*pValue > target) {
                    *pValue = target;
                }
            } else {
                if (*pValue < target) {
                    *pValue = target;
                }
            }
        } else {
            if (stepSize > 0.0f) {
                *pValue += minStep;
                if (*pValue > target) {
                    *pValue = target;
                }
            } else {
                *pValue += negMinStep;
                if (*pValue < target) {
                    *pValue = target;
                }
            }
        }
    }

    return target - *pValue;
}

/**
 * @brief Add a calculated value to a variable to approach a target value with a maximum step limit.
 *
 * This function adds a calculated step size to the input variable to approach the target value.
 * The step size is calculated based on the fraction and is limited by the maximum step value.
 *
 * @param pValue Pointer to the input variable.
 * @param target Target value to approach.
 * @param fraction Fraction to use in the step size calculation.
 * @param maxStep Maximum allowed step size.
 */
extern void add_calc2(f32* pValue, f32 target, f32 fraction, f32 maxStep) {
    f32 stepSize;

    if (*pValue != target) {
        stepSize = fraction * (target - *pValue);

        if (stepSize > maxStep) {
            stepSize = maxStep;
        } else if (stepSize < -maxStep) {
            stepSize = -maxStep;
        }

        *pValue += stepSize;
    }
}

/**
 * @brief Step a variable towards 0 by a fixed fraction, with a specified maximum possible step.
 *
 * @param pValue Pointer to the input variable.
 * @param fraction Fraction to use in the step size calculation.
 * @param maxStep Maximum allowed step size.
 */
extern void add_calc0(f32* pValue, f32 fraction, f32 maxStep) {
    f32 stepSize = *pValue * fraction;

    if (stepSize > maxStep) {
        stepSize = maxStep;
    } else if (stepSize < -maxStep) {
        stepSize = -maxStep;
    }

    *pValue -= stepSize;
}

/**
 * @brief Add a calculated value to a short integer variable to approach a target angle with minimum and maximum step
 * limits.
 *
 * This function adds a calculated step size to the input short integer variable to approach the target angle.
 * The step size is calculated based on the fraction and is limited by the minimum and maximum step values.
 *
 * @param pValue Pointer to the input short integer variable.
 * @param target Target angle to approach.
 * @param fraction Fraction to use in the step size calculation.
 * @param maxStep Maximum allowed step size.
 * @param minStep Minimum allowed step size.
 * @return The difference between the updated input variable angle and the target angle.
 */
extern s16 add_calc_short_angle2(s16* pValue, s16 target, f32 fraction, s16 maxStep, s16 minStep) {
    s16 stepSize = 0;
    s16 diff = target - *pValue;

    if (*pValue != target) {
        stepSize = (s16)(diff * fraction);

        if ((stepSize > minStep) || (stepSize < -minStep)) {
            if (stepSize > maxStep) {
                stepSize = maxStep;
            } else if (stepSize < -maxStep) {
                stepSize = -maxStep;
            }

            *pValue += stepSize;

            if (stepSize > 0) {
                if ((s16)(target - *pValue) < 0) {
                    *pValue = target;
                }
            } else {
                if ((s16)(target - *pValue) > 0) {
                    *pValue = target;
                }
            }
        } else {
            if (diff >= 0) {
                *pValue += minStep;
                if ((s16)(target - *pValue) < 0) {
                    *pValue = target;
                }
            } else {
                *pValue -= minStep;
                if ((s16)(target - *pValue) > 0) {
                    *pValue = target;
                }
            }
        }
    }
    return target - *pValue;
}

/**
 * @brief Add a calculated value to a short integer angle variable to approach a target angle with minimum and maximum
 * step limits.
 *
 * This function adds a calculated step size to the input short integer angle variable to approach the target angle.
 * The step size is calculated based on the fraction and is limited by the minimum and maximum step values.
 * Handles angle wrapping correctly.
 *
 * @param pValue Pointer to the input short integer angle variable.
 * @param target Target angle to approach.
 * @param fraction Fraction to use in the step size calculation.
 * @param maxStep Maximum allowed step size.
 * @param minStep Minimum allowed step size.
 * @return The difference between the updated input variable angle and the target angle.
 */
extern s16 add_calc_short_angle3(s16* pValue, s16 target, f32 fraction, s16 maxStep, s16 minStep) {
    f32 stepSize;
    s32 uTarget;
    s32 newValue;
    s32 uValue;

    if (target != *pValue) {
        uValue = (u16)*pValue;
        uTarget = (u16)target;

        if (uValue > uTarget) {
            uTarget += 65536; /* Add 360 short degrees */
        }

        stepSize = (uTarget - uValue) * fraction;

        if (stepSize > maxStep) {
            stepSize = maxStep;
        } else if (stepSize < minStep) {
            stepSize = minStep;
        }

        newValue = uValue + (s32)stepSize;
        if (newValue > uTarget) {
            newValue = uTarget;
        }
        *pValue = newValue;
    }

    return target - *pValue;
}

/**
 * @brief Copy RBGA color from one rgba_t to another.
 *
 * @param dest Pointer to the destination rgba_t variable.
 * @param src Pointer to the source rgba_t variable.
 */
extern void rgba_t_move(rgba_t* dest, const rgba_t* const src) {
    dest->r = src->r;
    dest->g = src->g;
    dest->b = src->b;
    dest->a = src->a;
}

/**
 * @brief A general purpose no-op function.
 *
 * @return 0
 */
extern int none_proc1() {
    return 0;
}

/**
 * @brief No-op function meant for use in actor profiles.
 *
 * @param actor Pointer to an ACTOR structure.
 * @param game Pointer to a GAME structure.
 */
extern void none_proc2(ACTOR* actor, GAME* game) {
}

/**
 * @brief Check if the game is in pause state.
 *
 * @param play Pointer to a GAME_PLAY structure.
 * @return TRUE if the game is in pause state, FALSE otherwise.
 */
extern int _Game_play_isPause(GAME_PLAY* play) {
    return (play->pause.enabled != 0);
}

/**
 * @brief Calculate a percentage with respect to minimum and maximum values, and apply scaling.
 *
 * - If `x` is closer to 0 than `min`, return 0
 * - If `x` is further from 0 than `max`, return the sign of `x`
 * - Otherwise, scale `x` by `scale` and return it.
 * If `shift_by_min`, move `x` by  `min` towards 0 before scaling it.
 *
 * @param x Input value to check.
 * @param min Minimum value for the range.
 * @param max Maximum value for the range.
 * @param scale Scaling factor to apply to the percentage.
 * @param shift_by_min Flag to shift the percentage by the minimum value (1 to shift, 0 not to shift).
 * @return Scaled percentage of the input value within the specified range.
 */
extern f32 check_percent_abs(f32 x, f32 min, f32 max, f32 scale, int shift_by_min) {
    if ((-min <= x) && (x <= min)) {
        return 0.0f;
    }
    if (x >= max) {
        return 1.0f;
    }
    if (x <= -max) {
        return -1.0f;
    }
    if (shift_by_min) {
        if (x > 0.0f) {
            return (x - min) * scale;
        } else {
            return (x + min) * scale;
        }
    } else {
        return x * scale;
    }
}

/**
 * @brief Calculate the percentage of completion based on acceleration and braking values.
 *
 * This function calculates the percentage of completion using the current position, start and end positions,
 * acceleration and braking distances using quadratic easing.
 *
 * @param now Current position value.
 * @param start Start position value.
 * @param end End position value.
 * @param accelerateDist Acceleration distance.
 * @param brakeDist Braking distance.
 * @return Percentage of completion.
 */
extern f32 get_percent_forAccelBrake(f32 now, f32 start, f32 end, f32 accelerateDist, f32 brakeDist) {
    f32 percent;
    f32 total_delta;
    f32 now_delta;
    f32 step;

    if (now >= end) {
        return 1.0f;
    }
    if (now <= start) {
        return 0.0f;
    }
    total_delta = end - start;
    now_delta = now - start;
    if (total_delta < (accelerateDist + brakeDist)) {
        return 0.0f;
    }

    step = 1.0f / (((2.0f * total_delta) - accelerateDist) - brakeDist);
    if (accelerateDist != 0.0f) {
        if (now_delta <= accelerateDist) {
            percent = (now_delta * (step * now_delta));
            percent /= accelerateDist;
            return percent;
        }
        percent = step * accelerateDist;
    } else {
        percent = 0.0f;
    }
    if (now_delta <= (total_delta - brakeDist)) {
        percent += (step * 2.0f) * (now_delta - accelerateDist);
        return percent;
    }
    percent += (2.0f * step * ((total_delta - accelerateDist) - brakeDist));
    if (brakeDist != 0.0f) {
        percent += step * brakeDist;
        if (now_delta < total_delta) {
            f32 diff = total_delta - now_delta;
            percent -= step * diff * diff / brakeDist;
        }
    }
    return percent;
}

/**
 * @brief Project a 3D world position onto a 2D screen position.
 *
 * @param play Pointer to a GAME_PLAY structure.
 * @param wpos Pointer to the 3D world position (xyz_t).
 * @param screen_pos Pointer to the resulting 2D screen position (xyz_t).
 */
extern void Game_play_Projection_Trans(GAME_PLAY* const play, xyz_t* world_pos, xyz_t* screen_pos) {
    f32 w;

    Matrix_mult(&play->projection_matrix, MTX_LOAD);
    Matrix_Position(world_pos, screen_pos);
    w = play->projection_matrix.ww +
        ((play->projection_matrix.wx * world_pos->x) + (play->projection_matrix.wy * world_pos->y) +
         (play->projection_matrix.wz * world_pos->z));
    screen_pos->x = (SCREEN_WIDTH_F / 2.0f) + ((screen_pos->x / w) * (SCREEN_WIDTH_F / 2.0f));
    screen_pos->y = (SCREEN_HEIGHT_F / 2.0f) - ((screen_pos->y / w) * (SCREEN_HEIGHT_F / 2.0f));
}

/**
 * @brief Calculate the percentage of the input value within the specified range.
 *
 * @param max Maximum value for the range.
 * @param min Minimum value for the range.
 * @param x Input value to check.
 * @return Percentage of the input value within the specified range.
 */
extern f32 get_percent(const int max, const int min, const int x) {
    f32 total_delta;
    f32 percent;

    percent = 1.0f;
    if (x < min) {
        percent = 0.0f;
    } else if (x < max) {
        total_delta = max - min;
        if (total_delta != 0.0f) {
            percent = (f32)(x - min) / total_delta;
            if (percent > 1.0f) {
                percent = 1.0f;
            }
        }
    }
    return percent;
}
