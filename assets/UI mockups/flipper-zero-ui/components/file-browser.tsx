"use client"

import { useState } from "react"
import DisplayFrame from "./display-frame"

interface FileBrowserProps {
  onBack: () => void
}

export default function FileBrowser({ onBack }: FileBrowserProps) {
  const [selectedFile, setSelectedFile] = useState(0)

  const files = [
    { icon: "📁", name: "infrared", type: "dir" },
    { icon: "📁", name: "subghz", type: "dir" },
    { icon: "📁", name: "nfc", type: "dir" },
    { icon: "📁", name: "ibutton", type: "dir" },
    { icon: "📄", name: "garage.sub", type: "file" },
    { icon: "📄", name: "tv_samsung.ir", type: "file" },
    { icon: "📄", name: "access_card.nfc", type: "file" },
  ]

  return (
    <DisplayFrame title="File Browser" onBack={onBack}>
      <div className="flex flex-col h-full">
        <div className="text-[8px] mb-1">/ext/</div>

        <div className="flex flex-col">
          {files.map((file, index) => (
            <div
              key={index}
              className={`flex items-center py-0.5 px-1 cursor-pointer text-[10px] ${selectedFile === index ? "bg-[#00FFFF] text-black" : ""}`}
              onClick={() => setSelectedFile(index)}
            >
              <span className="w-4 text-center mr-1">{file.icon}</span>
              <span className="truncate">{file.name}</span>
            </div>
          ))}
        </div>

        <div className="mt-auto text-[8px] flex justify-between">
          <span>7 items</span>
          <span>OK to open</span>
        </div>
      </div>
    </DisplayFrame>
  )
}
