import {createApi, fetchBaseQuery} from '@reduxjs/toolkit/query/react';
import { setTraks } from '../slices/traklistSlice';
import { setFavorites, deleteFavorite, addFavorite } from '../slices/favoritesSlice';
import { setUserinfo } from '../slices/userinfoSlice';
import {RequestUrl} from '../constants'
import {createSuccessMessage, createErrorMessage} from '../components/Messages'
import {ITrak} from '../types'

export const Api = createApi({
    reducerPath: 'Api',
    baseQuery: fetchBaseQuery({
        baseUrl: RequestUrl        
    }),
    endpoints: (builder) => ({
        getTraks: builder.query({
            query: ({access_token}) => {

                console.log("query token = ", ("Bearer "+ localStorage.getItem("access_token")));
                return {url: '/traks',
                    headers: {
                        Authorization:  ("Bearer "+ localStorage.getItem("access_token"))
                    }
                };
            },

            async onQueryStarted(args, {dispatch, queryFulfilled}){
                const {data} = await queryFulfilled;
                console.log("myApi: getTraks", data)
                dispatch(setTraks(data)); //изменяет State в traklistSlice
            }
        }),

        addTrak: builder.mutation<{res:any},{trakItem: ITrak}> (
            {
                query ({trakItem}) {
                    console.log("Add track ", String(trakItem.guid));
                    return{
                        url: '/favorites/'+String(trakItem.guid),
                        method: 'POST',
                        headers: {
                            Authorization: ("Bearer "+ localStorage.getItem("access_token"))
                        }
                    }
                },
                async onQueryStarted(args, { dispatch, queryFulfilled }) {
                    try {
                        const res = await queryFulfilled;
                        dispatch(addFavorite(args.trakItem)); //favoritesSlice 
                        createSuccessMessage("Трек '"+args.trakItem.name+"' добавлен");                    
                    } 
                    catch (error) {
                        createErrorMessage("Не удалось добавить трек '"+args.trakItem.name+"'");
                    } 
                }

            }
        ),
        getFavorites: builder.query({
        
            query: () => {
                console.log("getFavorites");
                return {url: '/favorites',
                headers: {Authorization: ("Bearer "+ localStorage.getItem("access_token"))
                }};
            },
            async onQueryStarted(args, { dispatch, queryFulfilled }) {
                try{
                    const {data} = await queryFulfilled;
                    console.log("FAVOURITES!!!!! = ", data);
                    dispatch(setFavorites(data)); //изменяет State в favoritesSlice

                }
                catch (error) {
                }
            }
        }),

        delFavorite: builder.mutation<{result:any},{trakItem: ITrak}> (
            {
                query ({trakItem}) {
                    console.log("Del trak ", String(trakItem.guid));
                    return{
                        url: '/favorites/'+String(trakItem.guid),
                        method: 'DELETE',
                        headers: {
                            Authorization: ("Bearer "+ localStorage.getItem("access_token"))
                        }
                    }
                },
                async onQueryStarted(args, { dispatch, queryFulfilled }) {
                    try {
                        const res = await queryFulfilled;
                        dispatch(deleteFavorite(args.trakItem.guid)); //favoritesSlice 
                        createSuccessMessage("Трек '"+args.trakItem.name+"' удален");                    
                    } 
                    catch (error) {
                        createErrorMessage("Не удалось удалить трек '"+args.trakItem.name+"'");
                    } 
                }  
            }
        ),

        loginUser: builder.mutation<{Token: string}, //Результат запроса
                   {login:string, password:string}> // Параметры запроса
                   ({ query (data) {
                return {
                    url: '/users/login',
                    method: "POST",
                    body: data
                };
            },
            async onQueryStarted(args, { dispatch, queryFulfilled }) {
                try {
                  const { data } = await queryFulfilled;
                  localStorage.setItem("access_token", data.Token);
                  console.log("access_token from server = ", data.Token)
                } catch (error) {
                } 
            }      
        }),

        registerUser: builder.mutation<{Token: string}, //Результат запроса
                   {login:string, password:string}> // Параметры запроса
                   ({ query (data) {
                    console.log("REGISTER USER CALLED")
                return {
                    url: '/users/registration',
                    method: "POST",
                    body: data
                };
            },
            async onQueryStarted(args, { dispatch, queryFulfilled }) {
                try {
                  const { data } = await queryFulfilled;
                  localStorage.setItem("access_token", data.Token);
                  console.log("access_token from server = ", data.Token)
                
                } catch (error) {
               } 
            }      
        }),

        getUserinfo: builder.query({
            query: () => {
                return {url: '/account',
                headers: {Authorization: ("Bearer "+ localStorage.getItem("access_token"))
                }};
            },
            async onQueryStarted(args, { dispatch, queryFulfilled }) {
                try{
                    const {data} = await queryFulfilled;
                    dispatch(setUserinfo(data)); //изменяет State в userinfoSlice

                }
                catch (error) {
                }
            }
        }),
        editUserinfo: builder.mutation<{result:any}, {NewPassword: string}>({
            query: (data) => {
                console.log("newPassword = ", {data});
                return {url: '/account',
                method: 'PATCH',
                body: data,
                headers: {Authorization: ("Bearer "+ localStorage.getItem("access_token"))

                }};
            },
            async onQueryStarted(args, { dispatch, queryFulfilled }) {
                try{
                     await queryFulfilled;
                }
                catch (error) {
                }
            }
        }),
    })
})


export const {
    useGetTraksQuery,
    useAddTrakMutation,
    useGetFavoritesQuery,
    useDelFavoriteMutation,
    
    useLoginUserMutation,
    useRegisterUserMutation,
    useGetUserinfoQuery,
    useEditUserinfoMutation,
} = Api;