"use client"

import { useEffect, useState } from "react"
import DisplayFrame from "./display-frame"

interface NfcScanProps {
  onBack: () => void
}

export default function NfcScan({ onBack }: NfcScanProps) {
  const [scanProgress, setScanProgress] = useState(0)

  useEffect(() => {
    const interval = setInterval(() => {
      setScanProgress((prev) => {
        if (prev >= 100) {
          clearInterval(interval)
          return 100
        }
        return prev + 5
      })
    }, 200)

    return () => clearInterval(interval)
  }, [])

  return (
    <DisplayFrame title="NFC Scan" onBack={onBack}>
      <div className="flex flex-col h-full justify-between">
        <div className="text-center my-2">
          <div className="text-xs mb-2">Scanning for NFC tags...</div>
          <div className="animate-pulse">
            {Array.from({ length: 8 }).map((_, i) => (
              <span key={i} className="inline-block mx-0.5">
                {i % 2 === 0 ? "◢" : "◣"}
              </span>
            ))}
          </div>
        </div>

        <div className="mt-2">
          <div className="text-[8px] mb-1">Progress:</div>
          <div className="w-full h-2 border border-[#00FFFF] relative">
            <div className="absolute top-0 left-0 bottom-0 bg-[#00FFFF]" style={{ width: `${scanProgress}%` }}></div>
          </div>
          <div className="text-right text-[8px] mt-1">{scanProgress}%</div>
        </div>

        <div className="text-[8px] mt-2">Press BACK to cancel</div>
      </div>
    </DisplayFrame>
  )
}
