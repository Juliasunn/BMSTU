import { createSlice, PayloadAction } from "@reduxjs/toolkit";
import { ITrak, IPlaylist } from "../types";


const initialState:IPlaylist = {
    playlist: [],
    current:0,
    isPlaying: false
}


export const playerSlice = createSlice({
    initialState,
    name: "favoritesSlice",
    reducers: {
        setPlaylist: (state, action: PayloadAction<ITrak[]>) => {
            let newState = initialState;
            newState = {
                playlist: action.payload,
                current:0,
                isPlaying: false
            };
            return newState;


        },
        setTrak: (state, action: PayloadAction<ITrak>) => {
            console.log("set Trak ", action.payload);
            let newState = initialState;
            newState = {
                playlist: [action.payload],
                current:0,
                isPlaying: false
            };
            return newState;
        },

        setIsPlaying: (state, action: PayloadAction<boolean>) => {
            console.log("setIsPlaying: ", action.payload);
            let newState = state;
            newState.isPlaying=action.payload;
            console.log("newState: ", newState);
            return newState;

        },

        setCurrent: (state, action: PayloadAction<string>) => {
            console.log("setIsPlaying: ", action.payload);
            let newState = state;

            for (let i=0; i<state.playlist.length; i++) {
                if (state.playlist[i].guid === action.payload){
                    newState.current=i;
                    break;
                }
            }
            console.log("newState: ", newState);
            return newState;

        },

        setCurrentNext: (state) => {
            let newState = state;
            newState.current += 1;

            if (newState.current >= newState.playlist.length) {
                newState.current = 0;
            }
            return newState;

        },

        setCurrentPrev: (state) => {
            let newState = state;
            newState.current -= 1;

            if (newState.current < 0) {
                newState.current = 0;
            }
            return newState;

        }
    }

});

export default playerSlice.reducer;

export const {
    setPlaylist,
    setTrak,
    setIsPlaying,
    setCurrent,
    setCurrentPrev,
    setCurrentNext,

} = playerSlice.actions;