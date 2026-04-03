"use client"

import { useState } from "react"
import DisplayFrame from "./display-frame"

interface MainMenuProps {
  onSelect: (screen: string) => void
}

export default function MainMenu({ onSelect }: MainMenuProps) {
  const [selectedIndex, setSelectedIndex] = useState(0)

  const menuItems = [
    { icon: "📡", label: "NFC Tools", value: "nfc-tools" },
    { icon: "📻", label: "Sub-GHz Transmit", value: "subghz-transmit" },
    { icon: "📱", label: "Infrared Remote", value: "ir-remote" },
    { icon: "🔌", label: "GPIO Mode", value: "gpio-mode" },
    { icon: "📁", label: "File Browser", value: "file-browser" },
    { icon: "⚙️", label: "Settings", value: "settings" },
    { icon: "ℹ️", label: "System Info", value: "system-info" },
  ]

  // Handle keyboard navigation in a real implementation

  return (
    <DisplayFrame title="Main Menu" showBack={false}>
      <div className="flex flex-col">
        {menuItems.map((item, index) => (
          <div
            key={index}
            className={`flex items-center py-1 px-1 cursor-pointer ${selectedIndex === index ? "bg-[#00FFFF] text-black" : ""}`}
            onClick={() => {
              setSelectedIndex(index)
              onSelect(item.value)
            }}
          >
            <span className="w-4 text-center mr-1">{item.icon}</span>
            <span>{item.label}</span>
          </div>
        ))}
      </div>
    </DisplayFrame>
  )
}
