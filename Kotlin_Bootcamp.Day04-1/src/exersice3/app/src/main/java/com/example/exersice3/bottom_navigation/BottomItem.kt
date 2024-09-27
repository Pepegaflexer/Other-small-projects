package com.example.exersice3.bottom_navigation

import com.example.exersice3.R

sealed class BottomItem(val title: String, val iconId: Int, val route: String) {
    object GameScreen : BottomItem("Game Screen", R.drawable.game_icon, "game_screen")
    object About : BottomItem("About", R.drawable.about_icon, "about_screen")
}