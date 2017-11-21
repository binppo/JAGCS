#include "mission_list_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "mission.h"

#include "service_registry.h"
#include "mission_service.h"

using namespace presentation;

MissionListPresenter::MissionListPresenter(QObject* parent):
    BasePresenter(parent),
    m_service(domain::ServiceRegistry::missionService())
{
    connect(m_service, &domain::MissionService::missionAdded,
            this, &MissionListPresenter::updateMissions);
    connect(m_service, &domain::MissionService::missionRemoved,
            this, &MissionListPresenter::updateMissions);
}

void MissionListPresenter::updateMissions()
{
    QVariantList missionIds;
    for (const dao::MissionPtr& mission: m_service->missions())
    {
        missionIds.append(mission->id());
    }

    this->setViewProperty(PROPERTY(missionIds), missionIds);
}

void MissionListPresenter::addMission()
{
    dao::MissionPtr mission = dao::MissionPtr::create();
    mission->setName(tr("New Mission"));

    m_service->save(mission);
}
