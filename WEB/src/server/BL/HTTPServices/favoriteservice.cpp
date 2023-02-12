#include "favoriteservice.h"
#include "../Tools/tools.h"
#include <exceptionsdb.h>

boost::json::array FavoriteService::processGetFavs(const std::string &auth_field)
{
    int id =  auth_service_->get_id(auth_field);
    if (id == -1)
        throw auth_exception();

    FavoritesResource favorites = FavoritesResourceConverter::createFavoritesResource(fRepo->getUserTracks(id));
    boost::json::array trakJsonArr = p.favoritesToJsonArray(favorites);
    return trakJsonArr;
}

boost::json::value FavoriteService::processGetFav(const std::string &guid, const std::string &auth_field)
{
    boost::json::value trakJson;
    int id =  auth_service_->get_id(auth_field);
    if (id == -1)
        throw auth_exception();

    try {
        Track tr = fRepo->getUserTrack(guid, id);
        trakJson = p.trackToJson(TrakResourceConverter::createTrakResource(tr));

    }
    catch (forbidden_symb_exception &e) {
         throw invalid_params();
    }
    catch (...) {
        throw res_not_found_exception();
    }

    return trakJson;

}

bool FavoriteService::processPostFav(const std::string &guid, const std::string &auth_field)
{
    int id =  auth_service_->get_id(auth_field);
    if (id == -1)
        throw auth_exception();
    try {
        tRepo->getTrack(guid);
        fRepo->addTrack(guid, id);

    } catch (no_result_exception &e) {
        throw res_not_found_exception();
    }
    catch (forbidden_symb_exception &e) {
         throw invalid_params();
    }
    return true;

}

bool FavoriteService::processDeleteFav(const std::string &guid, const std::string &auth_field)
{
    int id =  auth_service_->get_id(auth_field);
    if (id == -1)
        throw auth_exception();//wrong format of auth field string;

    try {
        fRepo->getUserTrack(guid, id);
        fRepo->deleteTrack(guid, id);

    }
    catch (forbidden_symb_exception &e) {
         throw invalid_params();
    }
    catch (...) {
        throw res_not_found_exception();
    }
    return true;
}

FavoriteService::FavoriteService()
{
    fRepo = (RepoCreator::getCretor())->getUserTrackRepo();
    tRepo = std::shared_ptr<TrackRepo>((RepoCreator::getCretor())->getTrackRepo());
    auth_service_ = AuthService::get_service();
}
