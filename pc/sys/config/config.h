#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// Virtual configuration settings used in-memory by the application.
// Simple, header-only implementation with text-based persistence.

struct VirtualConfig {
	int width = 800;         // screen width
	int height = 600;        // screen height
	bool fullscreen = false; // fullscreen flag
	float masterVolume = 1.0f; // master volume 0.0 - 1.0
	std::string playerName = "Player";

	// Serialize to simple key=value lines
	std::string serialize() const {
		std::ostringstream o;
		o << "width=" << width << "\n";
		o << "height=" << height << "\n";
		o << "fullscreen=" << (fullscreen ? 1 : 0) << "\n";
		o << "masterVolume=" << masterVolume << "\n";
		o << "playerName=" << playerName << "\n";
		return o.str();
	}

	// Deserialize from key=value text; unknown keys ignored
	bool deserialize(const std::string &data) {
		std::istringstream in(data);
		std::string line;
		while (std::getline(in, line)) {
			if (line.empty()) continue;
			auto pos = line.find('=');
			if (pos == std::string::npos) continue;
			std::string key = line.substr(0, pos);
			std::string val = line.substr(pos + 1);
			try {
				if (key == "width") width = std::stoi(val);
				else if (key == "height") height = std::stoi(val);
				else if (key == "fullscreen") fullscreen = (std::stoi(val) != 0);
				else if (key == "masterVolume") masterVolume = std::stof(val);
				else if (key == "playerName") playerName = val;
			} catch (...) {
				// ignore malformed values
			}
		}
		return true;
	}

	bool loadFromFile(const std::string &path) {
		std::ifstream f(path);
		if (!f.is_open()) return false;
		std::ostringstream ss;
		ss << f.rdbuf();
		return deserialize(ss.str());
	}

	bool saveToFile(const std::string &path) const {
		std::ofstream f(path, std::ios::trunc);
		if (!f.is_open()) return false;
		f << serialize();
		return f.good();
	}
};

// Inline global instance (header-only). Use `gConfig` directly.
inline VirtualConfig gConfig;

#endif
