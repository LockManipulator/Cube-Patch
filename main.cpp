#include "main.h"
#include "cwmods/cwsdk.h"
#include <wchar.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <windows.h>

#include "src/memory/memory_helper.h"

class Mod : GenericMod {

	void VanillaGliderFix() {
		int glider_patch[] = { 0x49, 0x8B, 0xCD, 0xE8, 0x5A, 0x25, 0xDA, 0xFF, 0xF3, 0x0F, 0x10, 0xC8, 0x41, 0x0F, 0x28, 0xC7 };
		auto glider_find = MemoryHelper::FindPattern("F3 0F 5F C1 F3 0F 10 0D 06 0B 1F ? 0F 28 D1 F3");

		for (int i = 0; i < 16; i++) {
			MemoryHelper::PatchMemory<uint8_t>(glider_find + i, glider_patch[i]);
		}
	}

	void VanillaRideFix() {
		int ride_patch1[] = { 0x49, 0x8B, 0xCD, 0xE8, 0xDA, 0x94, 0xDA, 0xFF, 0x0F, 0x28, 0xF8 };
		int ride_patch2[] = { 0x0F, 0x1F, 0x40, 0x00, 0xF3, 0x44, 0x0F, 0x59, 0xCF };
		int ride_patch3[] = { 0xF3, 0x0F, 0x5C, 0xC1, 0xF3, 0x0F, 0x59, 0x05, 0xA3, 0xD5, 0x3C, 0x00, 0xF3, 0x0F, 0x58, 0x05, 0x17, 0x92, 0x3C, 0x00, 0xF3, 0x0F, 0x59, 0x05, 0x01, 0x00, 0x00, 0x00, 0xC3, 0x00, 0x00, 0xA0, 0x3F };

		auto ride_find1 = MemoryHelper::FindPattern("48 8B D3 49 8B CF E8 27 29 D5 FF");
		auto ride_find2 = MemoryHelper::FindPattern("F3 44 0F 59 0D 1A 27 17 ?");
		auto ride_find3 = MemoryHelper::FindPattern("F3 0F 5C C1 F3 0F 59 05 A3 D5 3C ? F3 0F 58 05 17 92 3C ? C3");

		for (int i = 0; i < 11; i++) {
			MemoryHelper::PatchMemory<uint8_t>(ride_find1 + i, ride_patch1[i]);
		}

		for (int i = 0; i < 9; i++) {
			MemoryHelper::PatchMemory<uint8_t>(ride_find2 + i, ride_patch2[i]);
		}

		for (int i = 0; i < 33; i++) {
			MemoryHelper::PatchMemory<uint8_t>(ride_find3 + i, ride_patch3[i]);
		}
	}

	virtual void Initialize() override {
		VanillaGliderFix();
		VanillaRideFix();
	}
};

EXPORT Mod* MakeMod() {
	return new Mod();
}
