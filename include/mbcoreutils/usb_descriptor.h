// Copyright 2013 MakerBot Industries

#ifndef INCLUDE_MBCOREUTILS_USB_DESCRIPTOR_H_
#define INCLUDE_MBCOREUTILS_USB_DESCRIPTOR_H_

#include <cstdint>
#include <string>

namespace MakerBot {

/// USB device descriptor
///
/// Identifies a device by vender ID, product ID, and serial
/// number. The serial number can be left empty (using the first
/// constructor) to identify a particular product without identifying
/// a particular machine of that product type.
class UsbDescriptor {
 public:
  typedef uint16_t VID;
  typedef uint16_t PID;
  typedef std::string Serial;

  /// Construct an invalid UsbDescriptor
  UsbDescriptor() {
  }

  /// Construct a UsbDescriptor with an empty serial number
  UsbDescriptor(const VID vid, const PID pid)
      : m_vid(vid),
        m_pid(pid) {
  }

  UsbDescriptor(const VID vid, const PID pid, const Serial &serial)
      : m_vid(vid),
        m_pid(pid),
        m_serial(serial) {
  }

  /// Vender ID
  VID vid() const {
    return m_vid;
  }

  /// Product ID
  PID pid() const {
    return m_pid;
  }

  /// Unique serial number
  Serial serial() const {
    return m_serial;
  }

  /// Equality test against another UsbDescriptor
  ///
  /// As a special case, leading '0' characters (zero, not null) in
  /// the serial number are ignored for purposes of comparison. For
  /// example, "6" is considered equal to "00000006".
  bool operator==(const UsbDescriptor &other) const {
    return ((m_vid == other.m_vid) &&
            (m_pid == other.m_pid) &&
            (normalizedSerial() == other.normalizedSerial()));
  }

 private:
  /// Return serial stripped of leading zero characters
  Serial normalizedSerial() const {
    const auto i(m_serial.find_first_not_of('0'));
    if (i == Serial::npos) {
      return Serial();
    } else {
      return m_serial.substr(i);
    }
  }

  VID m_vid;
  PID m_pid;
  Serial m_serial;
};
}

#endif  // INCLUDE_MBCOREUTILS_USB_DESCRIPTOR_H_
