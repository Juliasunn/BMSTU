import { createSlice, PayloadAction } from "@reduxjs/toolkit";
import { IDataUser } from "../types";

const initialState: IDataUser = {login:""}; 

export const userinfoSlice = createSlice({
    initialState,
    name: "userinfoSlice",
    reducers: {
        setUserinfo: (state, action: PayloadAction<IDataUser>) => {
            console.log("userinfoSlice: setUserinfo ", action.payload);
            let newState = action.payload;
            return newState;
        }
    }
});

export default userinfoSlice.reducer;

export const {
    setUserinfo
} = userinfoSlice.actions;