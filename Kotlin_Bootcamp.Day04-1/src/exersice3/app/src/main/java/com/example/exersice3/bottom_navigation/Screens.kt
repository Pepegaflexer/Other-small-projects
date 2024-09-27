package com.example.exersice3.bottom_navigation

import AboutScreen
import androidx.compose.runtime.Composable
import androidx.compose.ui.platform.LocalContext
import androidx.navigation.NavController
import com.example.exersice3.screens.GameScreen


@Composable
fun GameScreenForNavigation() {
    GameScreen(context = LocalContext.current)
}

@Composable
fun About(navController: NavController) {
    AboutScreen(navController = navController)
}