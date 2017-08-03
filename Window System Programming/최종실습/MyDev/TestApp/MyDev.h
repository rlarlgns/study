#pragma once
extern "C" __declspec(dllimport) bool InitMyDev(int nLevel);
extern "C" __declspec(dllimport) int GetMyDevError(void);
extern "C" __declspec(dllimport) bool GetMyDevPosition(int *x, int *y);
extern "C" __declspec(dllimport) void ReleaseMyDev(void);