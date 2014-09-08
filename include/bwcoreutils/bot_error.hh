#ifndef ERROR_QSTRINGS_HH
#define ERROR_QSTRINGS_HH

#include <QString>
#include "bwcoreutils/all_errors.hh"

namespace bwcoreutils {
	
/*
 * This class takes an error code integer and provides details for UI
 * error handling, including Qt translatable strings.
 * Requires Qt
 */
class BotError {
public:
	enum TYPE {
		NONE,
		TOOL_ERROR,
		FILAMENT_ERROR,
		GENERAL_ERROR,
		ZPAUSE,
		SAD_BOT,
        CHAMBER_ERROR
	};
	
	enum ACTION {
		ACKNOWLEDGE,
		CHANGE_FILAMENT,
		PREHEAT_TIMEOUT,
		ZPAUSED,
        UNLOAD_FILAMENT
	};
	
	BotError(int errorCode) :
		m_type(GENERAL_ERROR),
		m_action(ACKNOWLEDGE) {
		init(errorCode);
	}
	
	~BotError() {
	}
	
	QString message() const {
		return m_message;
	}
	
	TYPE type() const {
		return m_type;
	}

	ACTION action() const {
		return m_action;
	}
	
	QString title() const {
		if(!m_title.isEmpty()) {
			return m_title;
		} else if(m_type == TOOL_ERROR) {
			return QObject::tr("Extruder Error");
		} else {
			return QObject::tr("System Error");
		}
	}
	
private:
	void init(int errorCode) {		
		switch(static_cast<Error>(errorCode)) {
			case kNoFilament:
				m_title = QObject::tr("Out of Filament");
				m_message = QObject::tr("Please unload your remaining filament, and then load new filament to continue printing (Warning %1).").arg(errorCode);
				m_type = FILAMENT_ERROR;
				m_action = CHANGE_FILAMENT;
				break;
			case kFilamentSlip:
				m_title = QObject::tr("Filament Jam");
				m_message = QObject::tr("Your filament seems to be jammed (Error %1). Please unload your remaining filament, and then reload it to continue printing.").arg(errorCode);
				m_type = FILAMENT_ERROR;
				m_action = CHANGE_FILAMENT;
				break;
            case kDoorInterlockTriggered:
                m_title = QObject::tr("Chamber Open");
                m_message = QObject::tr("The heated build chamber is open (Warning %1). Please close the door to continue.").arg(errorCode);
                m_type = CHAMBER_ERROR;
                break;
		    case kChamberProgramFailure:
				m_title = QObject::tr("Chamber Program Failed");
				m_message = QObject::tr("The build chamber heater controller cannot be programmed (Error %1). Please visit our Support page at Makerbot.com/support.").arg(errorCode);
				break;
		    case kCarriageProgramFailure:
				m_title = QObject::tr("Carriage Program Failed");
				m_message = QObject::tr("The extruder carriage cannot be programmed (Error %1). Please visit our Support page at Makerbot.com/support.").arg(errorCode);
				break;
		    case kChamberNotConnected:
				m_title = QObject::tr("Chamber Heater Disconnect");
				m_message = QObject::tr("The build chamber heater controller is disconnected (Error %1). Please visit our Support page at Makerbot.com/support.").arg(errorCode);
				break;
		    case kCarriageNotConnected:
				m_title = QObject::tr("Carriage Disconnected");
				m_message = QObject::tr("The extruder carriage is disconnected from the machine (Error %1). Please visit our Support page at Makerbot.com/support.").arg(errorCode);
				break;
			case kPrintToolConnectFailed:
				m_message = QObject::tr("Smart Extruder Connect Failed (Error %1).  Please disconnect your Smart Extruder and try again.").arg(errorCode);
				m_type = TOOL_ERROR;
				break;
			case kThermocoupleUnplugged:
			case kThermocoupleOutOfRange:
			case kThermocoupleTooHot:
			case kThermocoupleCommunicationFailure:
				m_message = QObject::tr("Oops, we have a problem with your Smart Extruder (Error %1: %2). Please disconnect and reconnect your Smart Extruder.").arg(errorCode).arg(QString::fromStdString(stringify_error(errorCode)));
				m_type = TOOL_ERROR;
				break;	
			case kNoToolConnected:
				m_message = QObject::tr("Your Smart Extruder is not connected (Error %1). Please reconnect your Smart Extruder.").arg(errorCode);
				m_type = TOOL_ERROR;
				break;
			case kHeaterShort:
			case kToolShort:
			case kToolFanShort:			
			case kMotorOverCurrent:
			case kFilamentFanShort:
			case kToolOpen:
			case kUnsupportedTool:
			case kToolReadError:
			case kToolChecksumFail:
			case kToolFanOpen:
			case kToolheadNoResponse:
			case kToolheadMismatchApiVersion:
			case kFilamentFanOpen:
			case kEepromChecksumFailure:
			case kToolheadNotInitialized:
			case kToolheadMalformedPacket:
			case kHeaterRiseWatchdogTriggered:
			case kHeaterTemperatureSagTriggered:
            case kHeaterTemperatureOverrunTriggered:
            case kWatchdogTriggered:
				m_message = QObject::tr("Oops, we have a problem with your Smart Extruder (Error %1: %2). Please visit our Support page at Makerbot.com/support.").arg(errorCode).arg(QString::fromStdString(stringify_error(errorCode)));
				m_type = TOOL_ERROR;
				break;	
			case kToolheadNotHeating:
				m_title = QObject::tr("Heating Error");
			    m_message = QObject::tr("DO NOT touch the extruder as it may be very hot (Error %1). Please visit our Support page at Makerbot.com/support.").arg(errorCode);
			    m_type = NONE;
			    break;
			case kHeaterHoldWatchdogTriggered:
				m_title = QObject::tr("Heating Timeout");
			    m_message = QObject::tr("Heaters were turned off due to inactivity (Warning %1)").arg(errorCode);
			    m_type = NONE;
			    break;
            case kNoHesChange:
				m_title = QObject::tr("Homing Error");
			    m_message = QObject::tr("Homing failed (Error %1). Your Smart Extruder is not communicating. Please try again.").arg(errorCode);
			    m_type = NONE;
			    break;			
            case kNoHesLog:
            case kUnknownHomingMethod:
			case kHomingNotCompleted:
			case kHomingTimedOut:
				m_title = QObject::tr("Homing Error");
			    m_message = QObject::tr("Homing failed (Error %1: %2). Please try again.").arg(errorCode).arg(QString::fromStdString(stringify_error(errorCode)));;
			    m_type = NONE;
			    break;			
            case kNoValidHesSlope:
            case kHesRebaseFailed:
            case kBinarySearchOutOfRange:
            case kHesLogOverflow:
            case kBadHesWaveforms:
				m_title = QObject::tr("Homing Error");
			    m_message = QObject::tr("Homing failed (Error %1). Your extruder nozzle may be stuck. Please try again.").arg(errorCode);
			    m_type = NONE;
			    break;			
			case kJsonToolpathNothingParsed:
			case kJsonToolpathParseError:
				m_title = QObject::tr("Print Error");
			    m_message = QObject::tr("Invalid print file (Error %1). Please try to prepare again in MakerBot Desktop.").arg(errorCode);
			    m_type = NONE;
			    break;	
			case kZPause:
				m_title = QObject::tr("Print Paused");
			    m_message = QObject::tr("Paused your print."); // TODO: height in mm?
			    m_type = ZPAUSE;
			    m_action = ZPAUSED;
			    break;				
			case kMismatchApiVersion:
			case kDefaultConfigMissingValue:
			case kDefaultConfigNotFound:
			case kDefaultConfigParseFailure:
			case kInvalidEepromFilepath:			    
			    m_message = QObject::tr("Oops, we have a problem (Error %1: %2). Please update your firmware using MakerBot Desktop.").arg(errorCode).arg(QString::fromStdString(stringify_error(errorCode)));
				break;	
            case kMoveCommandOutsideAxisBounds:
                m_title = QObject::tr("File Error");
			    m_message = QObject::tr("Error %1: Please make sure that your .makerbot file is prepared for the correct printer type.").arg(errorCode);
				break;	
			case kKaitenError:
			case kCriticalKaitenError:
				// don't show users the term 'Kaiten'
				m_message = QObject::tr("Oops, we have a problem (Error %1). ").arg(errorCode);
				break;
            case kLevelingWithFilament:
                m_title = QObject::tr("Clear Filament");
                m_message = QObject::tr("Please remove filament from the Smart Extruder before proceeding (Warning %1).").arg(errorCode);
                m_type = NONE;
                m_action = UNLOAD_FILAMENT;
                break;
            case kBothSidesTooHigh:
				m_title = QObject::tr("Leveling Error");
			    m_message = QObject::tr("Leveling failed (Error %1). Your extruder nozzle may be stuck. Please try again.").arg(errorCode);
			    m_type = NONE;
			    break;		
			case kNoBuildPlate:
				m_title = QObject::tr("No Build Plate");
			    m_message = QObject::tr("Please ensure your build plate is properly attached (Warning %1).").arg(errorCode);
			    m_type = NONE;
			    break;						
		    case kChamberThermistorDisconnected:
		    case kChamberHeaterDisconnected:
		    case kChamberHeaterFailure:
		    case kChamberFanFailure:
		    case kChamberTemperatureOverrun:
            case kHeaterOverTemp:
				m_message = QObject::tr("There is a problem with your chamber heater (Error %1: %2). Please visit our Support page at Makerbot.com/support.").arg(errorCode).arg(QString::fromStdString(stringify_error(errorCode)));
				break;
			case kInvalidResponse:
			case kUserConfigMissingValue:
			case kHeatZeroTemperature:
			case kEepromNoSlaveAck:
			case kHeaterAddFailure:
			case kEepromSlaveMissedValue:
			case kInvalidActiveToolSetting:
			case kThermocoupleAdcBusy:
			case kToolheadCommandTxFailure:
			case kInvalidFileType:
			case kUserConfigParseFailure:
			case kNoToolheadsDetected:
			case kZPauseValueNotFound:
			case kDiagnosticsUnknownStateError:
			case kInvalidEncoderResolution:
			case kInvalidAccelerationBufferSize:
			case kUserConfigNotFound:
			case kHeaterOpen:
			case kFileAlreadyOpen:
			case kExtrusionDistanceMissing:
			case kParseMore:
			case kBadToolCountConfig:
			case kPowerMonitorI2CFailure:
			case kEepromOutOfDate:
			case kOk:
			case kNone:
			case kInvalidAxis:
			case kInvalidHeaterIndex:
			case kDiagnostisUknownTestError:
			case kInvalidToolRequested:
			case kMachineDriverClosed:
			case kPruInitializationFailed:
	        case kEepromUnknownVersion:
            case kEepromStartFailure:
            case kEepromIdVerifyFail:
            case kZeroLengthMove:
            case kNotImplemented:
            case kNotReady:
            case kMachineDriverFailure:
            case kDiagnosticsTestFailed:
            case kEepromFatalInternalError:
            case kInterfaceLedCommsError:
            case kStopIteration:
            case kFileNotFound:
            case kBufferFull:
            case kSuspendNoValidLastMove:
            case kToolheadSpiConfigError:
            case kHeaterNotHeating:
            case kResumeComplete:
            case kCommandIndexMismatch:
            case kSuspendIndexNotFound:
            case kFileTransferTimeout:
            case kCorruptedFirmwareFile:
            case kKnobNotTightened:
            case kInvalidEndstopType:
            case kNoMacAddressSet:
            default:
                m_message = QObject::tr("Oops, we have a problem (Error %1: %2). ").arg(errorCode).arg(QString::fromStdString(stringify_error(errorCode)));
				break;
		}		
	}
	
	QString m_message;
	TYPE m_type;
	ACTION m_action;
	QString m_title;
};

	
} //namespace

#endif // ERROR_QSTRINGS_HH
