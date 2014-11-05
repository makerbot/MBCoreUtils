#ifndef INCLUDE_MBCOREUTILS_TOOLPATH_TAGS_H_
#define INCLUDE_MBCOREUTILS_TOOLPATH_TAGS_H_

namespace MakerBot {

enum ToolpathTag {
    kAnchor = 0,
    kBacklashCompensation,
    kBridge,
    kConnection,
    kFlickMove,//Not sure why there is Flick and FlickMove
    kInfill,
    kInset,
    kOutline,
    kLeakyTravelMove,
    kTravelMove,
    kTrailingExtrusionMove,
    kSpur,
    kSupport,
    kRetract,
    kRestart,
    kFlick,
    kLongRetract,
    kLongRestart,
    LAST
};

inline std::string stringFromToolpathTag(const ToolpathTag tag) {
    switch (tag) {
        case kAnchor:
            return "Anchor";
        case kBacklashCompensation:
            return "Backlash Compensation";
        case kBridge:
            return "Bridge";
        case kConnection:
            return "Connection";
        case kFlickMove:
            return "Flick Move";
        case kInfill:
            return "Infill";
        case kInset:
            return "Inset";
        case kOutline:
            return "Outline";
        case kLeakyTravelMove:
            return "Leaky Travel Move";
        case kTravelMove:
            return "Travel Move";
        case kTrailingExtrusionMove:
            return "Trailing Extrusion Move";
        case kSpur:
            return "Spur";
        case kSupport:
            return "Support";
        case kRetract:
            return "Retract";
        case kRestart:
            return "Restart";
        case kFlick:
            return "Flick";
        case kLongRetract:
            return "Long Retract";
        case kLongRestart:
            return "Long Restart";
        default:
            return "";
    }
}

inline int stringToToolpathTag(const std::string &str) {
    for(int i = 0; i < LAST; i++) {
        if (str == stringFromToolpathTag((ToolpathTag)i)) {
            return i;
        }
    }
    return -1;
}

}

#endif //INCLUDE_MBCOREUTILS_TOOLPATH_TAGS_H_
