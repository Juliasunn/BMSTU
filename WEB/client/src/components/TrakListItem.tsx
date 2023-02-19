import React from "react";
import '../index.css'
import { ITrak } from "../types";
import { ImMusic } from "react-icons/im"
import { useAppDispatch} from "../api/store";
import { MediaControlButton } from "./MediaControlButton";
import {FavControlButton} from "./FavoriteControlButton"

const trakItemContainerClass="p-2 m-1 flex flex-row place-content-between w-5/6 border backdrop-invert-0 bg-white/5 hover:bg-white/25 border-cyan-500/50 text-cyan-500"
const trakElementsContainerClass="py-2 px-3 flex flex-row space-x-3"


  interface TrakListItemProps {
    trakItem: ITrak,
  };


  const TrakListItem : React.FC<TrakListItemProps> = ({trakItem}) => {
    const dispatch = useAppDispatch();

    return (<div className={trakItemContainerClass}> 

      <div className={trakElementsContainerClass}>
      <ImMusic className="mx-2"></ImMusic>
        <h3>{trakItem.name}</h3>
      <h3 className="font-semibold text-cyan-700">{trakItem.artist}</h3>
      </div>
  
      <div className={trakElementsContainerClass}>
      <MediaControlButton trakItem={trakItem}></MediaControlButton>

    <FavControlButton trakItem={trakItem}></FavControlButton>
    </div>       
</div>)
  }
  
  
export default TrakListItem