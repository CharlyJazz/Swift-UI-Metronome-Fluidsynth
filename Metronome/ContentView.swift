//
//  ContentView.swift
//  Metronome
//
//  Created by Carlos Azuaje on 29/09/2022.
//

import SwiftUI

struct FormSlider: View {
    @State private var sliderValue: Double = 120
    
    var body: some View {
        Form {
            Section() {
                Slider(
                    value: $sliderValue,
                    in: 10...250,
                    step: 1
                )
            }.frame(width: 300)
        }
    }
}

// Remove the file:// from the URL because
// fluidsynth does not need it
func getSoundFontURL(filename: String) -> String {
    let absoluteString: String = Bundle.main.url(forResource: filename, withExtension: "sf2")?.absoluteString ?? ""
    let index = absoluteString.index(absoluteString.startIndex, offsetBy: 7)
    return String(absoluteString.suffix(from: index))
}

struct ContentView: View {
    @State var running: Bool = false
    @State var buttonText: String = "Start"

    var body: some View {
        VStack(alignment: .center) {
            Button(buttonText, action: {
                if (running == true) {
                    running = false
                    buttonText = "Start"
                } else {
                    running = true
                    buttonText = "Stop"
                    start_metronome(getSoundFontURL(filename: "S90ES"))
                }
            }).buttonStyle(DefaultButtonStyle())
            Divider()
            HStack(alignment: .center) {
                Text("Beats per second").padding()
                FormSlider()
            }
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView().frame(
            width: 500,
            height: 500
        );
    }
}
