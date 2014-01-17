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
		SAD_BOT
	};
	
	BotError(int errorCode) :
		m_message(QObject::tr("An error occurred")),
		m_type(GENERAL_ERROR) {
		init(errorCode);
	}
	
	~BotError() {
	}
	
	const QString message() const {
		return m_message;
	}
	
	const TYPE type() const {
		return m_type;
	}

private:
	void init(int errorCode) {		
		switch(static_cast<Error>(errorCode)) {
			case kNoFilament:
				m_message = QObject::tr("Out of filament - unload and reload filament");
				m_type = FILAMENT_ERROR;
				break;
			case kPrintToolNotConnected:
			case kToolheadNotConnected:
				m_message = QObject::tr("Reconnect this tool");
				m_type = TOOL_ERROR;
				break;
			case kNoToolConnected:
				m_message = QObject::tr("No tool connected");
				m_type = TOOL_ERROR;
				break;			
			case kDefaultConfigParseFailure:
			case kHomingNotCompleted:
			case kFilamentFanShort:
			case kThermocoupleUnplugged:
			case kInvalidResponse:
			case kDefaultConfigNotFound:
			case kUserConfigMissingValue:
			case kHeatZeroTemperature:
			case kEepromNoSlaveAck:
			case kHeaterWatchdogTriggered:
			case kToolOpen:
			case kEepromChecksumFailure:
			case kThermocoupleOutOfRange:
			case kHeaterAddFailure:
			case kEepromSlaveMissedValue:
			case kHeaterShort:
			case kToolShort:
			case kMismatchApiVersion:
			case kInvalidActiveToolSetting:
			case kToolheadNotInitialized:
			case kThermocoupleAdcBusy:
			case kToolheadCommandTxFailure:
			case kFilamentSlip:
			case kDefaultConfigMissingValue:
			case kCriticalKaitenError:
			case kInvalidFileType:
			case kUnsupportedTool:
			case kToolheadNotHeating:
			case kThermocoupleTooHot:
			case kUserConfigParseFailure:
			case kNoToolheadsDetected:
			case kToolheadProgramFailure:
			case kZPauseValueNotFound:
			case kDiagnosticsUnknownStateError:
			case kFilamentFanOpen:
			case kInvalidEncoderResolution:
			case kInvalidAccelerationBufferSize:
			case kUserConfigNotFound:
			case kHeaterOpen:
			case kFileAlreadyOpen:
			case kMotorOverCurrent:
			case kToolheadMismatchApiVersion:
			case kExtrusionDistanceMissing:
			case kInvalidEepromFilepath:
			case kJsonToolpathNothingParsed:
			case kToolFanShort:
			case kThermocoupleCommunicationFailure:
			case kParseMore:
			case kBadToolCountConfig:
			case kHomingTimedOut:
			case kPowerMonitorI2CFailure:
			case kEepromOutOfDate:
			case kOk:
			case kToolChecksumFail:
			case kToolheadNoResponse:
			case kToolFanOpen:
			case kKaitenError:
			case kNone:
			case kInvalidAxis:
			case kJsonToolpathParseError:
			case kInvalidHeaterIndex:
			case kDiagnostisUknownTestError:
			case kInvalidToolRequested:
			case kToolheadMalformedPacket:
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
			case kToolReadError:
			case kInterfaceLedCommsError:
			case kStopIteration:
			case kZPause:
			case kFileNotFound:
			default:
				break;
		}		
	}
	
	QString m_message;
	TYPE m_type;
};

	
} //namespace

#endif // ERROR_QSTRINGS_HH
