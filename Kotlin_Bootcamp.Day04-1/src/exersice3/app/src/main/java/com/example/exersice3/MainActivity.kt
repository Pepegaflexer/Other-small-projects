package com.example.exersice3

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import com.example.exersice3.bottom_navigation.MainScreen
import com.example.exersice3.ui.theme.Exersice3Theme

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            Exersice3Theme {
                MainScreen()
            }
        }
    }
}

