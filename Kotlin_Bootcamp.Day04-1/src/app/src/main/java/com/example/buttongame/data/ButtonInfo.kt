package com.example.buttongame.data

import androidx.compose.ui.graphics.Color

data class ButtonInfo(
    val defaultColor: Color,
    val pressedColor: Color,
    val width: Float,
    val soundResId: Int
) {
}