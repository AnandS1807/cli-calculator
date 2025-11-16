#pragma once

#include <string>

inline bool g_colors_enabled = true;

inline std::string RESET = "\033[0m";
inline std::string BOLD = "\033[1m";
inline std::string UNDERLINE = "\033[4m";
inline std::string RED = "\033[1;31m";
inline std::string GREEN = "\033[1;32m";
inline std::string YELLOW = "\033[1;33m";
inline std::string BLUE = "\033[1;34m";
inline std::string MAGENTA = "\033[1;35m";
inline std::string CYAN = "\033[1;36m";

inline void setColorsEnabled(bool enabled) {
	g_colors_enabled = enabled;
	if (enabled) {
		RESET = "\033[0m";
		BOLD = "\033[1m";
		UNDERLINE = "\033[4m";
		RED = "\033[1;31m";
		GREEN = "\033[1;32m";
		YELLOW = "\033[1;33m";
		BLUE = "\033[1;34m";
		MAGENTA = "\033[1;35m";
		CYAN = "\033[1;36m";
	} else {
		RESET.clear();
		BOLD.clear();
		UNDERLINE.clear();
		RED.clear();
		GREEN.clear();
		YELLOW.clear();
		BLUE.clear();
		MAGENTA.clear();
		CYAN.clear();
	}
}
