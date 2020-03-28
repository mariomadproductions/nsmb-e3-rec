#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	void nocashPrint(const char* format);
	void nocashPrint1(const char* format, int r0);
	void nocashPrint2(const char* format, int r0, int r1);
	void nocashPrint3(const char* format, int r0, int r1, int r2);
	void nocashPrint4(const char* format, int r0, int r1, int r2, int r3);

#ifdef __cplusplus
}
#endif /* extern "C" */