import { configureStore, getDefaultMiddleware } from '@reduxjs/toolkit'
import { TypedUseSelectorHook, useDispatch, useSelector } from "react-redux";
import {Api} from "./Api"
import traklistReducer from '../slices/traklistSlice'
import favoritesReducer from '../slices/favoritesSlice'
import userinfoReducer from '../slices/userinfoSlice'
import playerReducer from '../slices/playerSlice'

export const store = configureStore({
  reducer: {
    [Api.reducerPath]: Api.reducer, //Api.reducerPath was declared
    playerState: playerReducer,
    traklistState: traklistReducer,
    favoritesState: favoritesReducer,
    userinfoState: userinfoReducer
    
  },

  middleware: (getDefaultMiddleware) => (
    getDefaultMiddleware({}).concat(Api.middleware)
  )
})

export type RootState = ReturnType<typeof store.getState>;
export type AppDispatch = typeof store.dispatch;

export const useAppDispatch = () => useDispatch<AppDispatch>();

export const useAppSelector: TypedUseSelectorHook<RootState> = useSelector;

