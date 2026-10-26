.include "macros.inc"

.text
.balign 32

.global TRKAccessFile
.type TRKAccessFile, @function
TRKAccessFile:
	twi 31, r0, 0
	blr
.size TRKAccessFile, . - TRKAccessFile

.global TRKOpenFile
.type TRKOpenFile, @function
TRKOpenFile:
	twi 31, r0, 0
	blr
.size TRKOpenFile, . - TRKOpenFile

.global TRKCloseFile
.type TRKCloseFile, @function
TRKCloseFile:
	twi 31, r0, 0
	blr
.size TRKCloseFile, . - TRKCloseFile

.global TRKPositionFile
.type TRKPositionFile, @function
TRKPositionFile:
	twi 31, r0, 0
	blr
.size TRKPositionFile, . - TRKPositionFile
