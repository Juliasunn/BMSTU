#include "trakhttpservice.h"
#include <vector>
#include "../Tools/tools.h"
#include "../headers/req_exceptions.h"
#include <QDebug>
#include <exceptionsdb.h>

boost::json::array TrakHTTPService::ProcessGetTraks(const std::map<std::string, std::string> &query_params,
                                                    const std::string &auth_field)
{
    if (auth_service_->get_id(auth_field) == -1) {
        qDebug() << "auth service returned id = -1";
        throw auth_exception();
    }

    std::vector<TrakResource> favs = toTraksResource(tRepo->getTracks());
    boost::json::array trakJsonArr = p.tracksToJsonArray(favs);
    return trakJsonArr;
}

boost::json::value TrakHTTPService::ProcessGetTrak(const std::string &guid, const std::string &auth_field)
{
    if (auth_service_->get_id(auth_field) == -1)
        throw auth_exception();

    boost::json::value trakJson;

    try {
        Track tr = tRepo->getTrack(guid); //TODO: EXCEPTION
        trakJson = p.trackToJson(TrakResourceConverter::createTrakResource(tr));
    }
    catch (forbidden_symb_exception &e) {
         throw invalid_params();
    }
    catch (...) {
        throw res_not_found_exception(); //out of range
    }
    return trakJson;
}

TrakHTTPService::TrakHTTPService()
{
    tRepo = (RepoCreator::getCretor())->getTrackRepo();
    auth_service_ = AuthService::get_service();
}

std::vector<TrakResource> TrakHTTPService::toTraksResource(const std::vector<Track> &trList)
{
    std::vector<TrakResource> trResList;

    for (auto trak_ : trList){
        trResList.push_back(TrakResourceConverter::createTrakResource(trak_));
    }
    return trResList;
}
