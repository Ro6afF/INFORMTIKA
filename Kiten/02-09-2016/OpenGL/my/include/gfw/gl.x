#define X2(f,t) X(f,PFNGL##t##PROC)

X2(CreateShader, CREATESHADER)
X2(DeleteShader, DELETESHADER)
X2(ShaderSource, SHADERSOURCE)
X2(CompileShader, COMPILESHADER)
X2(GetShaderiv, GETSHADERIV)
X2(GetShaderInfoLog, GETSHADERINFOLOG)

X2(CreateProgram, CREATEPROGRAM)
X2(DeleteProgram, DELETEPROGRAM)
X2(AttachShader, ATTACHSHADER)
X2(DetachShader, ATTACHSHADER)
X2(LinkProgram, LINKPROGRAM)
X2(GetProgramiv, GETPROGRAMIV)
X2(GetProgramInfoLog, GETPROGRAMINFOLOG)
X2(UseProgram, USEPROGRAM)

X2(GenBuffers, GENBUFFERS)
X2(DeleteBuffers, DELETEBUFFERS)
X2(BindBuffer, BINDBUFFER)
X2(BufferData, BUFFERDATA)

X2(GenVertexArrays, GENVERTEXARRAYS)
X2(DeleteVertexArrays, DELETEVERTEXARRAYS)
X2(BindVertexArray, BINDVERTEXARRAY)
X2(EnableVertexAttribArray, ENABLEVERTEXATTRIBARRAY)
X2(DisableVertexAttribArray, DISABLEVERTEXATTRIBARRAY)
X2(VertexAttribPointer, VERTEXATTRIBPOINTER)
X2(VertexAttribIPointer, VERTEXATTRIBIPOINTER)
X2(VertexAttribLPointer, VERTEXATTRIBLPOINTER)
X2(VertexAttribDivisor, VERTEXATTRIBDIVISOR)

X2(UniformSubroutinesuiv, UNIFORMSUBROUTINESUIV)
X2(GetUniformLocation, GETUNIFORMLOCATION)
X2(Uniform1f, UNIFORM1F)
X2(Uniform1fv, UNIFORM1FV)
X2(Uniform1i, UNIFORM1I)
X2(Uniform1iv, UNIFORM1IV)
X2(Uniform1ui, UNIFORM1UI)
X2(Uniform1uiv, UNIFORM1UIV)
X2(Uniform2f, UNIFORM2F)
X2(Uniform2fv, UNIFORM2FV)
X2(Uniform2i, UNIFORM2I)
X2(Uniform2iv, UNIFORM2IV)
X2(Uniform2ui, UNIFORM2UI)
X2(Uniform2uiv, UNIFORM2UIV)
X2(Uniform3f, UNIFORM3F)
X2(Uniform3fv, UNIFORM3FV)
X2(Uniform3i, UNIFORM3I)
X2(Uniform3iv, UNIFORM3IV)
X2(Uniform3ui, UNIFORM3UI)
X2(Uniform3uiv, UNIFORM3UIV)
X2(Uniform4f, UNIFORM4F)
X2(Uniform4fv, UNIFORM4FV)
X2(Uniform4i, UNIFORM4I)
X2(Uniform4iv, UNIFORM4IV)
X2(Uniform4ui, UNIFORM4UI)
X2(Uniform4uiv, UNIFORM4UIV)
X2(UniformBlockBinding, UNIFORMBLOCKBINDING)
X2(UniformMatrix2fv, UNIFORMMATRIX2FV)
X2(UniformMatrix2x3fv, UNIFORMMATRIX2X3FV)
X2(UniformMatrix2x4fv, UNIFORMMATRIX2X4FV)
X2(UniformMatrix3fv, UNIFORMMATRIX3FV)
X2(UniformMatrix3x2fv, UNIFORMMATRIX3X2FV)
X2(UniformMatrix3x4fv, UNIFORMMATRIX3X4FV)
X2(UniformMatrix4fv, UNIFORMMATRIX4FV)
X2(UniformMatrix4x2fv, UNIFORMMATRIX4X2FV)
X2(UniformMatrix4x3fv, UNIFORMMATRIX4X3FV)

X2(DrawElementsInstanced, DRAWELEMENTSINSTANCED)

#undef X2
#undef X
