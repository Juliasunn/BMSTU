import { createSlice, PayloadAction } from "@reduxjs/toolkit";
import { ITrak } from "../types";

const initialState: ITrak[] = []; //массив избранных треков

export const favoritesSlice = createSlice({
    initialState,
    name: "favoritesSlice",
    reducers: {
        setFavorites: (state, action: PayloadAction<ITrak[]>) => {
            console.log("favoritesSlice: setFavorites ", action.payload);
            let newState: ITrak[] = [];
            for (let i = 0; i < action.payload.length; i++) {
                newState.push({
                    name: action.payload[i].name,
                    genre: action.payload[i].genre,
                    artist: action.payload[i].artist,
                    fileUrl: action.payload[i].fileUrl,
                    guid: action.payload[i].guid,
                    isFav: true
                });
            }
            return newState;
        },
        deleteFavorite: (state, action: PayloadAction<string>) => {
            state = state.filter( (trak) => (trak.guid !== action.payload));
            console.log("after delete len =  ",state.length, action.payload);
         return state;
        },

        addFavorite: (state, action: PayloadAction<ITrak>) => {
            state = state.filter( (trak) => (trak.guid !== action.payload.guid));
            state.push( action.payload);
            console.log("after add len =  ",state.length);
         return state;
        }
    }

});

export default favoritesSlice.reducer;

export const {
    setFavorites,
    deleteFavorite,
    addFavorite,
} = favoritesSlice.actions;