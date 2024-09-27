package com.example.exersice1.screens

import androidx.compose.foundation.interaction.MutableInteractionSource
import androidx.compose.foundation.interaction.PressInteraction
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.unit.dp
import kotlinx.coroutines.flow.collectLatest
import kotlinx.coroutines.flow.filterIsInstance

@Composable
fun PressableButton(
    onClick: () -> Unit,
    buttonColor: Color,
    pressedColor: Color,
    width: Float,

    ) {
    val interactionSource = remember { MutableInteractionSource() }
    var isPressed by remember { mutableStateOf(false) }

    LaunchedEffect(interactionSource) {
        interactionSource.interactions.filterIsInstance<PressInteraction>()
            .collectLatest { interaction ->
                when (interaction) {
                    is PressInteraction.Press -> {
                        isPressed = true

                    }

                    is PressInteraction.Release, is PressInteraction.Cancel -> isPressed = false
                }
            }
    }

    val finalColor = if (isPressed) pressedColor else buttonColor

    Button(
        modifier = Modifier
            .fillMaxHeight()
            .fillMaxWidth(width)
            .padding(5.dp),
        shape = RoundedCornerShape(10.dp),
        colors = ButtonDefaults.buttonColors(containerColor = finalColor),
        onClick = onClick,
        interactionSource = interactionSource
    ) {

    }
}