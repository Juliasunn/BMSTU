import '../index.css'

interface SelectWithLabelProps {
    labelText: string,
    options: string[],
    func: React.Dispatch<React.SetStateAction<string>>
  };
  
  
  export const SelectWithLabel: React.FC<(SelectWithLabelProps)> = ({labelText, options, func}) => {
    return (
    <div className="m-5 mx-10 flex flex-row space-x-4">
    <h1 className="m-3 text-lg font-bold text-cyan-500 shadow-xl">{labelText}: </h1>
    <select className="bg-black/50 text-gray-300 w-60 h-10 text-sm rounded-lg
     border border-gray-300 self-center"

     onChange={(event: React.ChangeEvent<HTMLSelectElement>) => (func(event.target.value))}>
     {options.map( (el) => (<option > {el} </option>) )}
  
      </select>
      </div>)
  }