import React, { RefCallback } from "react";
import { useAppDispatch, useAppSelector } from '../api/store';
import { useState } from "react";
import '../index.css'
import {setCurrentPrev, setIsPlaying, setCurrentNext} from '../slices/playerSlice'
import {ImPlay2} from "react-icons/im"
import {ImPause} from 'react-icons/im'
import {IoPlayBack} from 'react-icons/io5'
import {IoPlayForward} from 'react-icons/io5'
import {StaticUrl} from '../constants'

const TimeProgressbar : React.FC<{}> = () => {
  const el:HTMLMediaElement = document.getElementById("Player") as HTMLMediaElement;

  let fullTime:number = 100;
  const [currentTime, setCurrentTime] = useState(0);

  if (el != null) {
    fullTime = el.duration;
    el.addEventListener('timeupdate', (event) => {
    setCurrentTime(el.currentTime);
     });  
  }

return (<progress id="time" className="w-full h-3"
 max={fullTime} value={currentTime} >  </progress>)
}


const PlayerItem : React.FC<{}> = () => {

  const currentPlaylist = useAppSelector( (state) => state.playerState);
  const dispatch = useAppDispatch();

  if ((currentPlaylist.playlist).length <= currentPlaylist.current) {
    return (<div><h1>Ничего не воспроизводится</h1>
    <audio autoPlay id="Player"></audio></div>)
  }
  
  const currentPlaying = currentPlaylist.playlist[currentPlaylist.current];
  const source = StaticUrl+currentPlaying.fileUrl;
  const el:HTMLMediaElement = document.getElementById("Player") as HTMLMediaElement;

  if (currentPlaylist.isPlaying === true) {
    if (el.currentSrc !== source) {
      el.src=source;
    }
    el.play();
  }
  else if (el !== null) {
    el.pause();
  }

  const pauseHandler = () => {
    el.pause();
    dispatch(setIsPlaying(false));
  }

  const playHandler = () => {
    el.play();
    dispatch(setIsPlaying(true));
  }

  const prevHandler = () => {
    dispatch(setCurrentPrev());
  }

  const nextHandler = () => {
    dispatch(setCurrentNext());
  }

  return (
    <div className="mt-5 p-8  flex flex-col w-1/2 bg-black/50">

     <div className="flex flex-row justify-center place-content-center w-full ">
      <IoPlayBack className="IoPlayBack" onClick={prevHandler} ></IoPlayBack>

      <ImPlay2  className="ImPlay2" onClick={playHandler}></ImPlay2>

      <ImPause  className="ImPause" onClick={pauseHandler}></ImPause>

      <IoPlayForward className="IoPlayForward" onClick={nextHandler} ></IoPlayForward>
      </div>

    <h1 className="text-lg my-5 font-bold text-cyan-500 shadow-xl">Сейчас играет: {currentPlaying.name}</h1>
    <TimeProgressbar></TimeProgressbar>
    
    <audio autoPlay id="Player"></audio>
  </div>
    )
};

export default PlayerItem