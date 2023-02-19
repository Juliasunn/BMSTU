import React from 'react'
import '../index.css'
import { useGetFavoritesQuery } from '../api/Api';
import TrakList from '../components/TrakList';
import { useAppDispatch, useAppSelector } from '../api/store';
import PlayerItem from '../components/PlayerItem';
import LogoComponent from '../components/basic';
import { setPlaylist } from '../slices/playerSlice';
import { ToastContainer} from 'react-toastify';
import {MenuNavigate } from "../components/basic"

const FavoritesPage: React.FC<({})> = () => {

  useGetFavoritesQuery({},{ refetchOnMountOrArgChange: true });
  let currentFavorites = useAppSelector( (state) => state.favoritesState);

  const dispatch = useAppDispatch();
  dispatch(setPlaylist(currentFavorites));

  return (<div > <MenuNavigate></MenuNavigate>
    <div className="flex flex-col items-center justify-center mx-auto md:h-screen md:w-screen lg:py-0">
      <LogoComponent></LogoComponent>
       <h1 className="m-3 text-4xl font-bold text-cyan-500 shadow-xl">Избранные треки</h1>
      <TrakList data={currentFavorites}></TrakList>
      <ToastContainer />
      <PlayerItem ></PlayerItem>
    </div>
    </div>
  )

} 

export default FavoritesPage;