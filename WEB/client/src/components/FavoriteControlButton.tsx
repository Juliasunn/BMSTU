import React, { RefCallback, useEffect } from "react";
import '../index.css'
import {IoHeartDislikeOutline} from 'react-icons/io5'
import {IoHeartOutline} from 'react-icons/io5'
import { ITrak } from "../types";
import { useAddTrakMutation, useDelFavoriteMutation} from '../api/Api'
import { deleteFavorite, addFavorite } from "../slices/favoritesSlice";
import { useAppSelector, useAppDispatch} from "../api/store";
import {createSuccessMessage, createErrorMessage} from './Messages'
export {MediaControlButton} from './MediaControlButton'


interface TrakListButtonProps {
  trakItem: ITrak,
};

const AddFavButton : React.FC<TrakListButtonProps> = ({trakItem}) => {
  const [addTrak, resAdd] = useAddTrakMutation();
  const dispatch = useAppDispatch();


  const addFavHandler = (guid : string) => {
    console.log("Add trak guid = ", guid);
    addTrak({trakItem});
}
  return (
      <IoHeartOutline className="AddDelBtn" 
      onClick={()=> addFavHandler(trakItem.guid)}>
      </IoHeartOutline>
    )
};

const DelFavButton : React.FC<TrakListButtonProps> = ({trakItem}) => {
  const [delTrak, resDel] = useDelFavoriteMutation();
  const dispatch = useAppDispatch();

  const delFavHandler = () => {
    console.log("Del trak guid = ", trakItem.guid);
    delTrak({trakItem});
}
  return (
      <IoHeartDislikeOutline className="AddDelBtn" 
      onClick={()=> delFavHandler()}>
      </IoHeartDislikeOutline>
    )
};


interface FavControlButtonProps {
  trakItem: ITrak,
};


export const FavControlButton : React.FC<FavControlButtonProps> = ({trakItem}) => {

const currentFavorites= useAppSelector( (state) => state.favoritesState);
const dispatch = useAppDispatch();

for (let i = 0; i < currentFavorites.length; i++) {
  if ( (trakItem.isFav === true) || (currentFavorites[i].guid === trakItem.guid)) {
    return <DelFavButton trakItem={trakItem}></DelFavButton>
  }
}
return <AddFavButton trakItem={trakItem}></AddFavButton>
};