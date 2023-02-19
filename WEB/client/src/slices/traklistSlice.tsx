import { createSlice, PayloadAction } from "@reduxjs/toolkit";
import { ITrak } from "../types";

const initialState: ITrak[] = []; //массив треков

export const traklistSlice = createSlice({
    initialState,
    name: "traklistSlice",
    reducers: {
        setTraks: (state, action: PayloadAction<ITrak[]>) => {
            console.log("traklistSlice: setTraks ", action.payload);
            let newState: ITrak[] = [];
            for (let i = 0; i < action.payload.length; i++) {
                newState.push({
                    name: action.payload[i]["name"],
                    genre: action.payload[i]["genre"],
                    artist: action.payload[i]["artist"],
                    fileUrl: action.payload[i]["fileUrl"],
                    guid: action.payload[i]["guid"],
                    isFav: false
                });
            }

            return newState;
        },

        filterByGenre (state, action: PayloadAction<string>) {
            console.log("payload = ", action.payload);
            const newState = state.filter( (trak) => (trak.genre === action.payload));
            return newState;
        },

        findByName (state, action: PayloadAction<string>) {
            console.log("payload = ", action.payload);
            if (action.payload.length === 0) {
                return state;
            }
            const newState = state.filter( (trak) => (
                (trak.name).indexOf(action.payload) === 0));
            return newState;
        }
    }

});

export default traklistSlice.reducer;

export const {
    setTraks,
    filterByGenre,
    findByName
} = traklistSlice.actions;