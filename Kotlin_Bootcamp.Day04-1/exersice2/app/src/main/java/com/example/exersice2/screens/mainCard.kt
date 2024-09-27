package com.example.buttongame.screens


import android.content.Context
import android.media.MediaPlayer
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.AlertDialog
import androidx.compose.material3.Button
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.rememberCoroutineScope
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.unit.dp
import com.example.buttongame.R
import com.example.buttongame.data.ButtonInfo
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import kotlin.random.Random


fun playSound(context: Context, soundResId: Int) {
    val mediaPlayer = MediaPlayer.create(context, soundResId)
    mediaPlayer.start()
    mediaPlayer.setOnCompletionListener {
        it.release()
    }
}


@Composable
fun GameScreen(context: Context) {
    var level by remember { mutableIntStateOf(1) } // Уровень игры
    var sequence by remember { mutableStateOf(listOf<Int>()) } // Последовательность игры
    var userProgress by remember { mutableIntStateOf(0) } // Прогресс пользователя
    var gameOver by remember { mutableStateOf(false) } // Флаг окончания игры
    val coroutineScope = rememberCoroutineScope() // Короутины для задержки
    var buttonsEnabled by remember { mutableStateOf(false) } // Флаг включения кнопок
    var freeGame by remember { mutableStateOf(false) }

    val buttons = listOf(
        ButtonInfo(Color.Gray, Color.Yellow, 0.5f, R.raw.click_sound1),
        ButtonInfo(Color.Blue, Color.Yellow, 1.0f, R.raw.click_sound2),
        ButtonInfo(Color.Magenta, Color.Yellow, 0.5f, R.raw.click_sound3),
        ButtonInfo(Color.Unspecified, Color.Yellow, 1.0f, R.raw.click_sound4)
    )
    var buttonColors by remember { mutableStateOf(buttons.map { it.defaultColor }) }

    suspend fun playSequence() {
        delay(500)
        for (index in sequence) {
            val button = buttons[index]
            buttonColors =
                buttonColors.toMutableList().apply { this[index] = buttons[index].pressedColor }
            playSound(context, button.soundResId)
            delay(500) // Задержка между звуками
            buttonColors =
                buttonColors.toMutableList().apply { this[index] = buttons[index].defaultColor }
        }
    }

    fun startNewLevel() {
        sequence = sequence + Random.nextInt(4)
        userProgress = 0
        buttonsEnabled = false
        coroutineScope.launch {
            playSequence()
            buttonsEnabled = true // Включаем кнопки после показа последовательности
        }
    }


    fun handleButtonPress(buttonIndex: Int) {
        if (!buttonsEnabled) return
        if (freeGame)playSound(context, buttons[buttonIndex].soundResId)
        if (buttonIndex == sequence[userProgress] && (!freeGame)) {
            playSound(context, buttons[buttonIndex].soundResId)
            userProgress++
            if (userProgress == sequence.size) {
                level++
                startNewLevel()
            }
        } else {
            gameOver = true
        }
    }
    if (!freeGame) {
        // Начало игры
        LaunchedEffect(Unit) {
            sequence = List(3) { Random.nextInt(4) }
            startNewLevel()
        }
    }
    Column(modifier = Modifier.fillMaxSize(), verticalArrangement = Arrangement.Center) {
        var text = ""
        if (freeGame) text = "Free Game" else text = "Level: $level"
        Text(
            text = text,
            modifier = Modifier.padding(16.dp),
            style = MaterialTheme.typography.headlineMedium
        )

        Row(
            modifier = Modifier
                .fillMaxWidth()
                .fillMaxHeight(0.25f)
                .padding(all = 10.dp),
            horizontalArrangement = Arrangement.SpaceEvenly,
        ) {
            buttons.take(2).forEachIndexed { index, buttonInfo ->
                PressableButton(
                    onClick = { handleButtonPress(index) },
                    buttonColor = buttonColors[index],
                    pressedColor = buttonInfo.pressedColor,
                    width = buttonInfo.width,
                    context = context,
                )
            }
        }

        Row(
            modifier = Modifier
                .fillMaxWidth()
                .fillMaxHeight(0.30f)
                .padding(start = 10.dp, end = 10.dp),
            horizontalArrangement = Arrangement.SpaceEvenly
        ) {
            buttons.drop(2).forEachIndexed { index, buttonInfo ->
                PressableButton(
                    onClick = { handleButtonPress(index + 2) },
                    buttonColor = buttonColors[index + 2],
                    pressedColor = buttonInfo.pressedColor,
                    width = buttonInfo.width,
                    context = context,
                )
            }
        }

    if (!freeGame) {
        if (gameOver) {
            GameOverDialog(level - 1) {
                level = 1
                sequence = List(3) { Random.nextInt(4) }
                gameOver = false
                startNewLevel()
            }
        }
    }
        Column(modifier = Modifier.fillMaxWidth())
        {
            Button(
                onClick = {
                    freeGame = false
                    level = 1
                    sequence = List(3) { Random.nextInt(4) } // Сбрасываем последовательность
                    gameOver = false
                    startNewLevel()
                }, modifier = Modifier
                    .fillMaxWidth()
                    .padding(top = 16.dp, start = 16.dp, end = 16.dp,)
            ) {
                Text(text = "New Game")
            }
                Button(
                    onClick = {
                        freeGame = true
                    }, modifier = Modifier
                        .fillMaxWidth()
                        .padding(start = 16.dp, end = 16.dp)
                ) {
                    Text(text = "Free Game")
                }
        }

    }

}

@Composable
fun GameOverDialog(level: Int, onRestart: () -> Unit) {
    AlertDialog(onDismissRequest = { /* Диалог можно закрыть */ },
        title = { Text("Game Over") },
        text = { Text("You reached level $level") },
        confirmButton = {
            Button(onClick = onRestart) {
                Text("Restart")
            }
        })
}





