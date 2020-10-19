#ifndef EXTRUDER_COMMON_HH
#define EXTRUDER_COMMON_HH

namespace extruder {

enum ExtruderType {
    MK14,
    MK14_S,
    MK14_HOT,
    MK14_HOT_S,
    MK14_E,
    MK14_C,
    MK14_HOT_E
}; // enum

inline int get_extruder_max_temp(ExtruderType val) {
    int retval;
    switch(val){
        case MK14:
        case MK14_S:
        case MK14_HOT:
        case MK14_HOT_S:
        case MK14_E:
        case MK14_C:
    	    retval = 310;
    	    break;
        case MK14_HOT_E:
    	    retval = 380;
    	    break;

        default:
            retval = 310;
    }
    return retval;
} //get_extruder_max_temp
} // namespace
#endif // EXTRUDER_COMMON_HH
