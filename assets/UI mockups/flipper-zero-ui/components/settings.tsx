"use client"

import { useState } from "react"
import DisplayFrame from "./display-frame"

interface SettingsProps {
  onBack: () => void
}

export default function Settings({ onBack }: SettingsProps) {
  const [selectedSetting, setSelectedSetting] = useState(0)

  const settings = [
    { label: "Display", value: "display" },
    { label: "Power", value: "power" },
    { label: "Bluetooth", value: "bluetooth" },
    { label: "USB", value: "usb" },
    { label: "About", value: "about" },
  ]

  return (
    <DisplayFrame title="Settings" onBack={onBack}>
      <div className="flex flex-col h-full">
        {settings.map((setting, index) => (
          <div
            key={index}
            className={`py-0.5 px-1 cursor-pointer ${selectedSetting === index ? "bg-[#00FFFF] text-black" : ""}`}
            onClick={() => setSelectedSetting(index)}
          >
            {setting.label}
          </div>
        ))}

        <div className="mt-auto text-[8px] text-center">Press OK to select</div>
      </div>
    </DisplayFrame>
  )
}
