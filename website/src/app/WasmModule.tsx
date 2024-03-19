"use client"
import { FC, useEffect, useRef, useState } from "react";
import createModule from "./application.mjs";

/**
 * TODO add a spinner when module is loading
 * TODO add an error message when module fails to load
 * TODO passing the module name as a prop to the component
 * TODO setting a type to the module
 * TODO styling the component
 */

type Props = {
};

const WasmModule: FC<Props> = ({} : Props) => {

    const [module, setModule] = useState<any | null>({});
    const canvasRef = useRef<HTMLCanvasElement | null>(null);

    useEffect(() => {
        createModule({ canvas: canvasRef.current }).then((module: any) => {
            setModule(module);
        });
    }, []);
    
    if (!module) return <div>Loading WebAssembly module...</div>;
    else return <canvas id="canvas" ref={canvasRef}></canvas>;
};

export default WasmModule;