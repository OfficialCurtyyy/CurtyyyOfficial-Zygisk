
#include "app_profiles.h"

#include <algorithm>
#include <fstream>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

namespace OfficialCurtyyyZygisk {

struct AppProfile {
    std::string packageName;
    std::string profileId;
};

static const std::vector<std::string> kSupportedProfiles = {
    "s26",
    "iphone18",
    "zfold8",
    "rog9",
    "rm10",
    "rm11s"
};

static std::vector<AppProfile> gProfiles;
static std::mutex gProfilesMutex;

static std::string trim(const std::string& value) {
    const std::string whitespace = " \t\r\n";

    const auto first = value.find_first_not_of(whitespace);
    if (first == std::string::npos) {
        return {};
    }

    const auto last = value.find_last_not_of(whitespace);
    return value.substr(first, last - first + 1);
}

bool isValidProfile(const std::string& profileId) {
    return std::find(
        kSupportedProfiles.begin(),
        kSupportedProfiles.end(),
        profileId
    ) != kSupportedProfiles.end();
}

bool loadAppProfiles(const std::string& filePath) {
    std::ifstream input(filePath);

    if (!input.is_open()) {
        return false;
    }

    std::vector<AppProfile> parsed;
    std::string line;

    while (std::getline(input, line)) {
        line = trim(line);

        if (line.empty() || line[0] == '#') {
            continue;
        }

        const std::size_t separator = line.find('|');

        if (separator == std::string::npos) {
            continue;
        }

        const std::string packageName =
            trim(line.substr(0, separator));

        const std::string profileId =
            trim(line.substr(separator + 1));

        if (packageName.empty() || !isValidProfile(profileId)) {
            continue;
        }

        parsed.push_back({packageName, profileId});
    }

    std::lock_guard<std::mutex> lock(gProfilesMutex);
    gProfiles = std::move(parsed);

    return true;
}

std::string getAppProfile(const std::string& packageName) {
    std::lock_guard<std::mutex> lock(gProfilesMutex);

    const auto it = std::find_if(
        gProfiles.begin(),
        gProfiles.end(),
        [&packageName](const AppProfile& profile) {
            return profile.packageName == packageName;
        }
    );

    if (it == gProfiles.end()) {
        return {};
    }

    return it->profileId;
}

bool hasAppProfile(const std::string& packageName) {
    return !getAppProfile(packageName).empty();
}

void clearAppProfiles() {
    std::lock_guard<std::mutex> lock(gProfilesMutex);
    gProfiles.clear();
}

std::size_t getProfileCount() {
    std::lock_guard<std::mutex> lock(gProfilesMutex);
    return gProfiles.size();
}

}
