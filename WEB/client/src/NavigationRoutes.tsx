import { Route, Routes } from "react-router-dom"
import AuthPage from "./pages/AuthPage"
import FavoritesPage from "./pages/FavoritesPage"
import MenuPage from "./pages/MenuPage"
import SearchPage from "./pages/SearchPage"

import { AuthPath, MenuPath, SearchPath, FavPath } from "./constants"

const NavigationRoutes = () => {
    return (
        <Routes>            
        <Route path={MenuPath} element={<MenuPage></MenuPage>}></Route> 
        <Route path={SearchPath} element={<SearchPage></SearchPage>}></Route>
        <Route path={AuthPath} element={<AuthPage></AuthPage>} ></Route>
        <Route path={FavPath} element={<FavoritesPage></FavoritesPage>}></Route>
        </Routes>
    )
}

export default NavigationRoutes;