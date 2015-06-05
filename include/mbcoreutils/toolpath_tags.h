#ifndef INCLUDE_MBCOREUTILS_TOOLPATH_TAGS_H_
#define INCLUDE_MBCOREUTILS_TOOLPATH_TAGS_H_

namespace MakerBot {

enum ToolpathTag : unsigned int{
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
        case LAST:
        default:
            return "";
    }
}

inline int stringToToolpathTag(const std::string &str) {
    for(unsigned i = 0; i < LAST; i++) {
        if (str == stringFromToolpathTag((ToolpathTag)i)) {
            return i;
        }
    }
    return -1;
}

enum AxisUnit {
    kMilliMetre=0,
    kMicroMetre,
    kMilliLitre,
    kMicroLitre,
    kLast
};

inline std::string stringFromAxisUnit(const AxisUnit unit) {
    switch(unit) {
    case kMilliMetre:
        return "mm";
    case kMicroMetre:
        return "um";
    case kMilliLitre:
        return "ml";
    case kMicroLitre:
        return "ul";
    case kLast:
    default:
        return "";
    }
}

inline int stringToAxisUnit(const std::string& str) {
    for(int i = 0; i < kLast; i++) {
        if (str == stringFromAxisUnit((AxisUnit)i)) {
            return i;
        }
    }
    return -1;
}
}
   
#endif // INCLUDE_MBCOREUTILS_TOOLPATH_TAGS_H_
