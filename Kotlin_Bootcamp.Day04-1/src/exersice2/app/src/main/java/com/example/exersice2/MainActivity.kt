package com.example.exersice2

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.ui.platform.LocalContext
import com.example.exersice2.screens.GameScreen
import com.example.exersice2.ui.theme.Exersice2Theme

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            Exersice2Theme {
                GameScreen(context= LocalContext.current)
                }
            }
        }
    }

