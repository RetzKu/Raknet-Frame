#include <string>

std::wstring string_to_wstring(const std::string& text) {
	return std::wstring(text.begin(), text.end());
}