#include "rest_network.h"

////////////////////////////////////////////////////////////////////////////////
/// Network2Rover
////////////////////////////////////////////////////////////////////////////////

Network2Rover::Network2Rover() : left_joystick(0), right_joystick(0), current_mode(STOP) {
    //Empty Constructor
}

void Network2Rover::SetLeftJoystick(int lJoy) {
    left_joystick = lJoy;
}

void Network2Rover::SetRightJoystick(int rJoy) {
    right_joystick = rJoy;
}

void Network2Rover::SetRunMode(run_mode newMode) {
    current_mode = newMode;
}

int Network2Rover::GetLeftJoystick() const {
    return left_joystick;
}

int Network2Rover::GetRightJoystick() const {
    return right_joystick;
}

Network2Rover::run_mode Network2Rover::GetRunMode() const {
    return current_mode;
}

QByteArray Network2Rover::ToByteArray() const {
    return QString("%1:%2:%3\n").arg(QString::number(left_joystick), QString::number(right_joystick), QString::number(static_cast<int>(current_mode))).toUtf8();
}

bool Network2Rover::ParseData(QByteArray data) {
    QStringList list = QString(data).split(":");

    if (list.size() < NUM_PARAMS) return false;

    left_joystick = list.at(0).toInt();
    right_joystick = list.at(1).toInt();
    current_mode = static_cast<run_mode>(list.at(2).toInt());

    return true;
}

////////////////////////////////////////////////////////////////////////////////
/// Network2Base
////////////////////////////////////////////////////////////////////////////////

Network2Base::Network2Base() : new_picture(false) {

}

void Network2Base::SetImage(QImage &image_in) {
    image = image_in;
}

QImage Network2Base::GetImage() const {
    return image;
}

bool Network2Base::HasNewImage() const {
    return new_picture;
}

QByteArray Network2Base::ToByteArray() const {
    QByteArray byteArray;

    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);

    image.save(&buffer, "JPG");

    byteArray.push_back('\n');

    return byteArray;
}

bool Network2Base::ParseString(QString data) {
    QByteArray byteArray = data.toUtf8();

    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::ReadOnly);

    return new_picture = image.load(&buffer, "JPG");
}


