package com.example.exersice3.bottom_navigation

import androidx.compose.runtime.Composable
import androidx.navigation.NavHostController
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable

@Composable
fun NavGraph(navHostController: NavHostController) {
    NavHost(navController = navHostController, startDestination = "game_screen"){
        composable("game_screen") {
            GameScreenForNavigation()
        }
        composable("about_screen"){
            About(navController = navHostController)
        }
    }
}