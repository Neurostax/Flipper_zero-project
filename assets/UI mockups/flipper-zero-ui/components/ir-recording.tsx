"use client"

import { useState, useEffect } from "react"
import DisplayFrame from "./display-frame"

interface IrRecordingProps {
  onBack: () => void
}

export default function IrRecording({ onBack }: IrRecordingProps) {
  const [isRecording, setIsRecording] = useState(true)
  const [signalStrength, setSignalStrength] = useState<number[]>([])

  useEffect(() => {
    if (isRecording) {
      const interval = setInterval(() => {
        setSignalStrength((prev) => {
          const newValue = Math.floor(Math.random() * 10)
          const newArray = [...prev, newValue]
          if (newArray.length > 20) {
            return newArray.slice(1)
          }
          return newArray
        })
      }, 200)

      return () => clearInterval(interval)
    }
  }, [isRecording])

  return (
    <DisplayFrame title="IR Recording" onBack={onBack}>
      <div className="flex flex-col h-full">
        <div className="text-center my-1">{isRecording ? "Recording IR signal..." : "Recording complete"}</div>

        <div className="flex items-end h-12 mt-2 border-b border-[#00FFFF]">
          {signalStrength.map((value, index) => (
            <div key={index} className="w-1 bg-[#00FFFF] mx-0.5" style={{ height: `${value * 10}%` }}></div>
          ))}
        </div>

        <div className="flex justify-between mt-2 text-[8px]">
          <button className="border border-[#00FFFF] px-1" onClick={() => setIsRecording(!isRecording)}>
            {isRecording ? "STOP" : "START"}
          </button>
          <button className="border border-[#00FFFF] px-1">SAVE</button>
        </div>
      </div>
    </DisplayFrame>
  )
}
