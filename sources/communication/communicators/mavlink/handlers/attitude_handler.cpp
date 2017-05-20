#include "attitude_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QtMath>

// Internal
#include "vehicle_service.h"
#include "base_vehicle.h"

using namespace comm;
using namespace domain;

AttitudeHandler::AttitudeHandler(VehicleService* vehicleService,
                                 MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_vehicleService(vehicleService)
{}

void AttitudeHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_ATTITUDE) return;

    BaseVehicle* vehicle = m_vehicleService->baseVehicle(message.sysid);
    if (!vehicle) return;

    mavlink_attitude_t attitude;
    mavlink_msg_attitude_decode(&message, &attitude);

    vehicle->setAttitude(Attitude(qRadiansToDegrees(attitude.pitch),
                                  qRadiansToDegrees(attitude.roll),
                                  qRadiansToDegrees(attitude.yaw)));
}