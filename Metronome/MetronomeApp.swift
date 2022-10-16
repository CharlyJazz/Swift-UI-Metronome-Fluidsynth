//
//  MetronomeApp.swift
//  Metronome
//
//  Created by Carlos Azuaje on 29/09/2022.
//


import SwiftUI

@main
struct MetronomeApp: App {
    var body: some Scene {
        WindowGroup {
            ContentView().frame(
                width: 500,
                height: 500
            ).onDisappear {
                finish_metronome()
            }
        }
    }
}
