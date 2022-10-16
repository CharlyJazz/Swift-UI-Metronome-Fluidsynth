//
//  ContentView.swift
//  Metronome
//
//  Created by Carlos Azuaje on 29/09/2022.
//

import SwiftUI

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
    @State private var sliderValue: Double = 120
    
    var body: some View {
        VStack(alignment: .center) {
            Button(buttonText, action: {
                if (running == true) {
                    running = false
                    buttonText = "Start"
                    finish_metronome()
                } else {
                    running = true
                    buttonText = "Stop"
                    start_metronome(getSoundFontURL(filename: "S90ES"), UInt32(sliderValue))
                }
            }).buttonStyle(DefaultButtonStyle())
            Divider()
            HStack(alignment: .center) {
                Text(String(sliderValue)).padding()
                Form {
                    Section() {
                        Slider(
                            value: $sliderValue,
                            in: 10...250,
                            step: 1,
                            onEditingChanged: { data in
                                if (running == true) {
                                    finish_metronome()
                                }
                                running = true
                                buttonText = "Stop"
                                start_metronome(getSoundFontURL(filename: "S90ES"), UInt32(sliderValue))
                            }
                        )
                    }.frame(width: 300)
                }
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
