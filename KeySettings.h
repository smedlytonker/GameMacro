#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <shared_mutex>
#include ".\SimpleIni\SimpleIni.h"

class KeySettings
{
public:
	struct KeyInList {
		uint8_t keyCode;
		std::string name;
		std::string keyCodeStr;
	};

	class PlaybackKey
	{
	public:
		uint8_t keyCode = 0;
		uint16_t delayInMS = 0;
		bool bShift = false;
		bool bCtrl = false;
		bool bAlt = false;
		bool bWKey = false;

		std::string name;
		std::string keyCodeStr;
		std::string delayInMSStr;
	};

	class MacroKey
	{
	public:
		uint8_t keyCode = 0;
		bool bLoop = false;
		std::vector<PlaybackKey> keys;
	};

	struct KeyLookUp {
		uint8_t keyCode;
		const char* name;
		bool bValid;
	};

public: 
	// filename only
	bool Create(char* fileName);
	bool Destroy();
	const char* KeySettings::DecodeKey(uint8_t keyCode);
	bool GetAvialableMacroKeys(std::vector<KeyInList>& keys, uint8_t currentKeyCode);
	bool GetAvialablePlaybackKeys(std::vector<KeyInList>& keys);
	bool GetMacroKeyList(std::vector<KeyInList>& list);
	bool AddMacroKey(MacroKey& macroKey);
	bool DeleteMacroKey(uint8_t keyCode);
	bool IsValidMacroKey(uint8_t keyCode);
	bool GetMacroKey(uint8_t keyCode, MacroKey& macroKey, bool bNoDecode = false);
	bool GetPlaybackKey(uint8_t macroKeyCode, int playbackKeyVectorIdx, PlaybackKey& playbackKey);
	bool AddPlaybackKey(uint8_t macroKeyCode, int playbackKeyVectorIdx, PlaybackKey& playbackKey);
	bool DeletePlaybackKey(uint8_t macroKeyCode, int playbackKeyVectorIdx);
	
private:
	bool IsMacroKey(uint8_t keyCode);
	bool ParseSection(CSimpleIniA& m_ini, MacroKey& key, const char* sectionName);
	bool ParseIni(CSimpleIniA& m_ini);
		
private:
	CSimpleIniA m_ini;
	WCHAR fullPathToFile[MAX_PATH] = { 0 };
	std::map<uint8_t, MacroKey> m_macroKeys;

	// Can't use std::mutex because I'm compiling with /clr option.
	// https://developercommunity.visualstudio.com/t/shared-mutex-and-clr/469913
	std::shared_mutex protectSettings;
};

extern KeySettings settings;