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
				m_message = QObject::tr("Please unload your remaining filament, and then load new filament to continue printing.");
				m_type = FILAMENT_ERROR;
				m_action = CHANGE_FILAMENT;
				break;
			case kFilamentSlip:
				m_title = QObject::tr("Filament Jam");
				m_message = QObject::tr("Your filament seems to be jammed. Please unload your remaining filament, and then reload it to continue printing.");
				m_type = FILAMENT_ERROR;
				m_action = CHANGE_FILAMENT;
				break;
            case kDoorInterlockTriggered:
                m_title = QObject::tr("Chamber Open");
                m_message = QObject::tr("The heated build chamber is open. Your print has been paused. Please close the door to continue printing.");
                m_type = CHAMBER_ERROR;
                break;
			case kPrintToolNotConnected:
			case kToolheadNotConnected:
			case kThermocoupleUnplugged:
			case kThermocoupleOutOfRange:
			case kThermocoupleTooHot:
			case kThermocoupleCommunicationFailure:
				m_message = QObject::tr("Oops, we have a problem with your Smart Extruder (Error %1: %2). Please disconnect and reconnect your Smart Extruder.").arg(errorCode).arg(QString::fromStdString(stringify_error(errorCode)));
				m_type = TOOL_ERROR;
				break;	
			case kNoToolConnected:
				m_message = QObject::tr("Your Smart Extruder is not connected. Please reconnect your Smart Extruder.");
				m_type = TOOL_ERROR;
				break;
            case kLevelingTimedOut:
            	m_title = QObject::tr("Leveling Timeout");
			    m_message = QObject::tr("Leveling has ended due to inactivity.");
			    m_type = NONE;
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
			case kToolheadProgramFailure:
			case kToolheadNotHeating:
			case kEepromChecksumFailure:
			case kToolheadNotInitialized:
			case kToolheadMalformedPacket:
			case kHeaterRiseWatchdogTriggered:
			case kHeaterTemperatureSagTriggered:
            case kHeaterTemperatureOverrunTriggered:
            case kWatchdogTriggered:
				m_message = QObject::tr("Oops, we have a problem with your Smart Extruder (Error %1: %2). Please contact MakerBot support.").arg(errorCode).arg(QString::fromStdString(stringify_error(errorCode)));
				m_type = TOOL_ERROR;
				break;	
			case kHeaterHoldWatchdogTriggered:
				m_title = QObject::tr("Heating Timeout");
			    m_message = QObject::tr("Heaters were turned off due to inactivity");
			    m_type = NONE;
			    break;
            case kNoHesChange:
				m_title = QObject::tr("Homing Error");
			    m_message = QObject::tr("Homing failed. Your Smart Extruder is not communicating. Please try again or contact Makerbot support.");
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
				m_title = QObject::tr("Homing Error");
			    m_message = QObject::tr("Homing failed. Your extruder nozzle may be stuck. Please try again.");
			    m_type = NONE;
			    break;			
			case kJsonToolpathNothingParsed:
			case kJsonToolpathParseError:
				m_title = QObject::tr("Print Error");
			    m_message = QObject::tr("Invalid print file. Please try to prepare again in MakerBot Desktop.");
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
			case kKaitenError:
			case kCriticalKaitenError:
				// don't show users the term 'Kaiten'
				m_message = QObject::tr("Oops, we have a problem (Error %1). ").arg(errorCode);
				break;
            case kLevelingWithFilament:
                m_title = QObject::tr("Clear Filament");
                m_message = QObject::tr("Please remove filament from the Smart Extruder before proceeding with assisted leveling.");
                m_type = NONE;
                m_action = UNLOAD_FILAMENT;
                break;
            case kBothSidesTooHigh:
				m_title = QObject::tr("Leveling Error");
			    m_message = QObject::tr("Leveling failed. Your extruder nozzle may be stuck. Please try again.");
			    m_type = NONE;
			    break;		
			case kNoBuildPlate:
				m_title = QObject::tr("No Build Plate");
			    m_message = QObject::tr("Please ensure your build plate is properly attached.");
			    m_type = NONE;
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
            case kToolheadDisconnected:
            case kBufferFull:
            case kSuspendNoValidLastMove:
            case kToolheadSpiConfigError:
            case kHeaterNotHeating:
            case kResumeComplete:
            case kHeaterOverTemp:
            case kCommandIndexMismatch:
            case kSuspendIndexNotFound:
            case kFileTransferTimeout:
            case kCorruptedFirmwareFile:
            case kHesLogOverflow:
            case kBadHesWaveforms:
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
