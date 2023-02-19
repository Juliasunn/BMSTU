import React from "react";
import '../index.css'
import {CiPlay1} from 'react-icons/ci'
import {IoPause} from 'react-icons/io5'
import { ITrak } from "../types";
import { setIsPlaying, setCurrent } from "../slices/playerSlice";
import { useAppSelector, useAppDispatch} from "../api/store";


interface MediaControlButtonProps {
    trakItem: ITrak,
  };


export const MediaControlButton: React.FC<MediaControlButtonProps> = ({trakItem}) => {

  const currentPlaylist = useAppSelector( (state) => state.playerState);
  const dispatch = useAppDispatch();

  const pauseHandler = () => {
    console.log("Pause trak guid = ", trakItem.guid);
    dispatch(setIsPlaying(false));
  }

  const playBtnHandler = () => {
    console.log("playBtnHandler");
    dispatch(setCurrent(trakItem.guid));
    dispatch(setIsPlaying(true));  
  }
  
  if ((currentPlaylist.playlist).length > currentPlaylist.current) {
     const playingTrack = currentPlaylist.playlist[currentPlaylist.current];
      if ((playingTrack.guid  === trakItem.guid) && (currentPlaylist.isPlaying)) {
        return (<IoPause className="PlayBtn"  onClick={pauseHandler}></IoPause> )
      }
  }
  return ( <CiPlay1 className="PlayBtn"  onClick={playBtnHandler}  ></CiPlay1> )
  };