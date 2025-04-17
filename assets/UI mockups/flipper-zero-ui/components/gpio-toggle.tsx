"use client"

import { useState } from "react"
import DisplayFrame from "./display-frame"

interface GpioToggleProps {
  onBack: () => void
}

export default function GpioToggle({ onBack }: GpioToggleProps) {
  const [pins, setPins] = useState([
    { pin: "A7", state: false },
    { pin: "A6", state: false },
    { pin: "A4", state: true },
    { pin: "B3", state: false },
    { pin: "B2", state: false },
    { pin: "C1", state: true },
    { pin: "C0", state: false },
  ])

  const [selectedPin, setSelectedPin] = useState(0)

  const togglePin = (index: number) => {
    setPins((prev) => prev.map((pin, i) => (i === index ? { ...pin, state: !pin.state } : pin)))
  }

  return (
    <DisplayFrame title="GPIO Pin Control" onBack={onBack}>
      <div className="flex flex-col h-full">
        <div className="grid grid-cols-2 gap-1">
          {pins.map((pin, index) => (
            <div
              key={index}
              className={`flex justify-between border border-[#00FFFF] px-1 py-0.5 cursor-pointer ${selectedPin === index ? "bg-[#00FFFF] text-black" : ""}`}
              onClick={() => {
                setSelectedPin(index)
                togglePin(index)
              }}
            >
              <span>GPIO {pin.pin}</span>
              <span>{pin.state ? "HIGH" : "LOW"}</span>
            </div>
          ))}
        </div>

        <div className="mt-auto flex justify-between text-[8px]">
          <div>Selected: {pins[selectedPin].pin}</div>
          <div>State: {pins[selectedPin].state ? "HIGH" : "LOW"}</div>
        </div>
      </div>
    </DisplayFrame>
  )
}
