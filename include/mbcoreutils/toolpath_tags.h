// Copyright MakerBot 2020
#ifndef INCLUDE_MBCOREUTILS_TOOLPATH_TAGS_H_
#define INCLUDE_MBCOREUTILS_TOOLPATH_TAGS_H_

#include <string>

namespace MakerBot {

enum ToolpathTag : unsigned int {
    kAnchor = 0,
    kBacklashCompensation,
    kBridge,
    kBrims,
    kConnection,
    kFillRoofSurface,
    kFlickMove,  // Not sure why there is Flick and FlickMove
    kFloor,
    kInfill,
    kInset,
    kOutline,
    kLeakyTravelMove,
    kTravelMove,
    kTrailingExtrusionMove,
    kSolid,
    kSparse,
    kSpur,
    kSupport,
    kRetract,
    kRestart,
    kRaft,
    kRoof,
    kFlick,
    kPurge,
    kLongRetract,
    kLongRestart,
    kBeadModeExternal,
    kBeadModeExternalThick,
    kBeadModeExternalThicker,
    kBeadModeExternalThickest,
    kBeadModeInternal,
    kBeadModeInternalThick,
    kBeadModeInternalThicker,
    kBeadModeInternalThickest,
    kBeadModeUser1,
    kBeadModeUser2,
    kBeadModeUser3,
    kBeadModeUser4,
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
        case kBrims:
            return "Brims";
        case kConnection:
            return "Connection";
        case kFillRoofSurface:
            return "Fill Roof Surface";
        case kFlickMove:
            return "Flick Move";
        case kFloor:
            return "Floor";
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
        case kSolid:
            return "Solid";
        case kSparse:
            return "Sparse";
        case kSpur:
            return "Spur";
        case kSupport:
            return "Support";
        case kRetract:
            return "Retract";
        case kRestart:
            return "Restart";
        case kRaft:
            return "Raft";
        case kFlick:
            return "Flick";
        case kPurge:
            return "Purge";
        case kRoof:
            return "Roof";
        case kLongRetract:
            return "Long Retract";
        case kLongRestart:
            return "Long Restart";
        case kBeadModeExternal:
          return "BeadMode External";
        case kBeadModeExternalThick:
          return "BeadMode External Thick";
        case kBeadModeExternalThicker:
          return "BeadMode External Thicker";
        case kBeadModeExternalThickest:
          return "BeadMode External Thickest";
        case kBeadModeInternal:
          return "BeadMode Internal";
        case kBeadModeInternalThick:
          return "BeadMode Internal Thick";
        case kBeadModeInternalThicker:
          return "BeadMode Internal Thicker";
        case kBeadModeInternalThickest:
          return "BeadMode Internal Thickest";
        case kBeadModeUser1:
          return "BeadMode User1";
        case kBeadModeUser2:
          return "BeadMode User2";
        case kBeadModeUser3:
          return "BeadMode User3";
        case kBeadModeUser4:
          return "BeadMode User4";
        case LAST:
        default:
            return "";
    }
}

inline int stringToToolpathTag(const std::string &str) {
    for (unsigned i = 0; i < LAST; i++) {
        if (str == stringFromToolpathTag((ToolpathTag)i)) {
            return i;
        }
    }
    return -1;
}

enum AxisUnit {
    kMilliMetre = 0,
    kMicroMetre,
    kMilliLitre,
    kMicroLitre,
    kLast
};

inline std::string stringFromAxisUnit(const AxisUnit unit) {
    switch (unit) {
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
    for (int i = 0; i < kLast; i++) {
        if (str == stringFromAxisUnit((AxisUnit)i)) {
            return i;
        }
    }
    return -1;
}
}

#endif  // INCLUDE_MBCOREUTILS_TOOLPATH_TAGS_H_
