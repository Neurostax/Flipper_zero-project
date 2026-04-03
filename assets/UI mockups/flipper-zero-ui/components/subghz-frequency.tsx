"use client"

import { useState } from "react"
import DisplayFrame from "./display-frame"

interface SubGhzFrequencyProps {
  onBack: () => void
}

export default function SubGhzFrequency({ onBack }: SubGhzFrequencyProps) {
  const [frequency, setFrequency] = useState(433.92)
  const [selectedOption, setSelectedOption] = useState(0)

  const frequencyOptions = [
    { label: "433.92 MHz", value: 433.92 },
    { label: "315.00 MHz", value: 315.0 },
    { label: "868.35 MHz", value: 868.35 },
    { label: "Custom...", value: "custom" },
  ]

  return (
    <DisplayFrame title="Sub-GHz Frequency" onBack={onBack}>
      <div className="flex flex-col h-full">
        <div className="text-center my-2 text-lg font-bold">{frequency} MHz</div>

        <div className="flex flex-col">
          {frequencyOptions.map((option, index) => (
            <div
              key={index}
              className={`py-0.5 px-1 cursor-pointer ${selectedOption === index ? "bg-[#00FFFF] text-black" : ""}`}
              onClick={() => {
                setSelectedOption(index)
                if (typeof option.value === "number") {
                  setFrequency(option.value)
                }
              }}
            >
              {option.label}
            </div>
          ))}
        </div>

        <div className="mt-auto text-center text-[8px]">Press OK to select</div>
      </div>
    </DisplayFrame>
  )
}
