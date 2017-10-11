#include "presentation_context.h"

// Internal
#include "vehicle.h"
#include "link_description.h"
#include "mission.h"
#include "mission_assignment.h"
#include "mission_item.h"
#include "video_source.h"
#include "modes.h"
#include "command.h"
#include "log_message.h"

#include "translation_helper.h"

// Qt
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

using namespace presentation;

PresentationContext::PresentationContext()
{
    qmlRegisterUncreatableType<dao::Vehicle>(
                "JAGCS", 1, 0, "Vehicle", "Can't create entities in QML");
    qmlRegisterUncreatableType<dao::LinkDescription>(
                "JAGCS", 1, 0, "LinkDescription", "Can't create entities in QML");
    qmlRegisterUncreatableType<dao::Mission>(
                "JAGCS", 1, 0, "Mission", "Can't create entities in QML");
    qmlRegisterUncreatableType<dao::MissionAssignment>(
                "JAGCS", 1, 0, "MissionAssignment", "Can't create entities in QML");
    qmlRegisterUncreatableType<dao::MissionItem>(
                "JAGCS", 1, 0, "MissionItem", "Can't create entities in QML");
    qmlRegisterUncreatableType<dao::VideoSource>(
                "JAGCS", 1, 0, "VideoSource", "Can't create entities in QML");
    qmlRegisterUncreatableType<domain::Command>(
                "JAGCS", 1, 0, "Command", "Can't create commands in QML");
    qmlRegisterUncreatableType<domain::LogMessage>(
                "JAGCS", 1, 0, "LogMessage", "Can't create log messages in QML");

    qmlRegisterUncreatableMetaObject(domain::staticMetaObject, "JAGCS", 1, 0, "Domain",
                                     "Can't create enums in QML");

    m_engine = new QQmlApplicationEngine(qApp);
    m_engine->rootContext()->setContextProperty("translator",
                                                QVariant::fromValue(new TranslationHelper(qApp)));
}

PresentationContext* PresentationContext::instance()
{
    static PresentationContext context;
    return &context;
}

QObject* PresentationContext::rootView()
{
    return instance()->m_engine->rootObjects().first();
}

QQmlContext* PresentationContext::rootContext()
{
    return instance()->m_engine->rootContext();
}

void PresentationContext::load()
{
    instance()->m_engine->load(QUrl("qrc:/Views/MainView.qml"));
    // TODO: wait objectCreated
}
