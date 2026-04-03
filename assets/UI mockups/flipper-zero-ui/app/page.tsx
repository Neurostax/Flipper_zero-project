"use client"

import { useState } from "react"
import MainMenu from "@/components/main-menu"
import NfcScan from "@/components/nfc-scan"
import IrRecording from "@/components/ir-recording"
import SubGhzFrequency from "@/components/subghz-frequency"
import GpioToggle from "@/components/gpio-toggle"
import SystemInfo from "@/components/system-info"
import FileBrowser from "@/components/file-browser"
import Settings from "@/components/settings"

export default function Home() {
  const [currentScreen, setCurrentScreen] = useState("main-menu")

  const renderScreen = () => {
    switch (currentScreen) {
      case "main-menu":
        return <MainMenu onSelect={(screen) => setCurrentScreen(screen)} />
      case "nfc-tools":
        return <NfcScan onBack={() => setCurrentScreen("main-menu")} />
      case "ir-remote":
        return <IrRecording onBack={() => setCurrentScreen("main-menu")} />
      case "subghz-transmit":
        return <SubGhzFrequency onBack={() => setCurrentScreen("main-menu")} />
      case "gpio-mode":
        return <GpioToggle onBack={() => setCurrentScreen("main-menu")} />
      case "system-info":
        return <SystemInfo onBack={() => setCurrentScreen("main-menu")} />
      case "file-browser":
        return <FileBrowser onBack={() => setCurrentScreen("main-menu")} />
      case "settings":
        return <Settings onBack={() => setCurrentScreen("main-menu")} />
      default:
        return <MainMenu onSelect={(screen) => setCurrentScreen(screen)} />
    }
  }

  return (
    <div className="flex items-center justify-center min-h-screen bg-gray-900 p-4">
      <div className="relative">
        <div className="border-4 border-gray-700 rounded-lg p-2 bg-black">
          <div className="w-[256px] h-[128px] relative overflow-hidden">{renderScreen()}</div>
        </div>
        <div className="absolute -right-16 top-1/2 -translate-y-1/2 flex flex-col gap-3">
          <button
            onClick={() => setCurrentScreen("main-menu")}
            className="w-10 h-10 rounded-full bg-gray-700 text-white flex items-center justify-center hover:bg-gray-600"
          >
            ↑
          </button>
          <button
            onClick={() => {
              if (currentScreen === "main-menu") {
                setCurrentScreen("nfc-tools")
              }
            }}
            className="w-10 h-10 rounded-full bg-gray-700 text-white flex items-center justify-center hover:bg-gray-600"
          >
            ↓
          </button>
          <button className="w-10 h-10 rounded-full bg-gray-700 text-white flex items-center justify-center hover:bg-gray-600">
            ←
          </button>
          <button className="w-10 h-10 rounded-full bg-gray-700 text-white flex items-center justify-center hover:bg-gray-600">
            →
          </button>
          <button className="w-10 h-10 rounded-full bg-gray-700 text-white flex items-center justify-center hover:bg-gray-600">
            OK
          </button>
        </div>
      </div>
    </div>
  )
}
